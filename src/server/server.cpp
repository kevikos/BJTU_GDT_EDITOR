#include				"Server.hpp"
#include				"Client.hpp"

int					main(int ac, char **av) {
    FDSet				fdSet;
    SocketTCPServer			server;
    std::vector<Client*>		clients;
    int					i;
    int					j;
    char				buff[1024];
    int					nbRead;

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
	Select::call(&fdSet, NULL);
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
		memset(buff, 0, 1024);
		if ((nbRead = clients[i]->getSocket()->receive(buff, 1024)) == 0)
		{
		    buff[nbRead] = 0;
		    clients[i]->getSocket()->close();
		    delete clients[i];
		    clients.erase(clients.begin() + i);
		}
		std::cout << buff[0] << std::endl;
		j = 0;
		while (j < clients.size())
		{
		    if (j != i)
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
    SocketTCP::stop();
}
