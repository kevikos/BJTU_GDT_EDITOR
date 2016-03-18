#include				"Server.hpp"
#include				"Client.hpp"

void					ejectClient(std::vector<Client*> clients, int i)
{
    clients[i]->getSocket()->close();
    delete clients[i];
    clients.erase(clients.begin() + i);
}

int					main(int ac, char **av) {
    FDSet				fdSet;
    SocketTCPServer			server;
    std::vector<Client*>		clients;
    int					i;
    int					j;
    char				buff[1024];
    int					nbRead;
    struct timeval			tv;
    
    if (ac != 2)
    {
	std::cout << "./server port" << std::endl;
	return (0);
    }
    SocketTCP::start();
    server.create("127.0.0.1", atoi(av[1]));
    while (true)
    {
	fdSet.zero();
	fdSet.set(&server);
	i = 0;
	while (i < clients.size())
	    fdSet.set(clients[i++]->getSocket());
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	if (Select::call(&fdSet, NULL, &tv) == false)
	{
	    std::cout << "Server : Socket managment failed" << std::endl;
	    return (-1);
	}
	if (fdSet.isset(&server))
	{
	    clients.push_back(new Client(server.acceptClient()));
	    clients[clients.size() - 1]->getSocket()->send("BIENVENU", 8);
	}
	i = 0;
	while (i < clients.size())
	{
	    if (fdSet.isset(clients[i]->getSocket()))
	    {
		clients[i]->show();
		memset(buff, 0, 1024);
		if ((nbRead = clients[i]->getSocket()->receive(buff, 1024)) == 0)
		{
		    buff[nbRead] = 0;
		    ejectClient(clients, i);
		}
		std::cout << buff << std::endl;
		if (std::string(buff).size() > 7 && std::string(buff).compare(0, 7, "player|") == 0)
		{
		    std::cout << "It's a client bitch" << std::endl;
		    std::cout << "His name is " << std::string(buff).substr(7, std::string(buff).length()) << std::endl;
		    clients[i]->setName(std::string(buff).substr(7, std::string(buff).length()));
		    clients[i]->setType(PLAYER);
		}
		if (std::string(buff).size() > 7 && std::string(buff).compare(0, 7, "editor|") == 0)
		{
		    std::cout << "It's a editor bitch" << std::endl;
		    std::cout << "His name is " << std::string(buff).substr(7, std::string(buff).length()) << std::endl;
		    clients[i]->setName(std::string(buff).substr(7, std::string(buff).length()));
		    clients[i]->setType(EDITOR);
		}
		if (clients[i]->getName() == "" && clients[i]->getType() == UNDEFINED)
		{
		    clients[i]->getSocket()->send("kick", 4);
		    ejectClient(clients, i);
		}
		j = 0;
		while (j < clients.size())
		{
		    if (j != i && clients[j]->getType() != EDITOR)
		    {
			std::cout << "SEND : " << buff << std::endl;
			clients[j]->getSocket()->send(buff, nbRead);
		    }
		    j++;
		}
	    }
	    i++;
	}
    }
//    SocketTCP::stop();
}
