#include				"Server.hpp"
#include				"Client.hpp"

void					ejectClient(std::vector<Client*> *clients, int i)
{
    (*clients)[i]->getSocket()->close();
    delete (*clients)[i];
    (*clients).erase((*clients).begin() + i);
}

int					init(int ac, char **av, SocketTCPServer *server)
{
    if (ac != 2)
    {
	std::cout << "Usage : ./server port" << std::endl;
	return (1);
    }
    if (!SocketTCP::start())
	return (-1);
    if (!server->create("127.0.0.1", atoi(av[1])))
	return (-1);
    return (0);
}

int					editorIsOnline(std::vector<Client*> *clients)
{
    int				i;

    i = 0;
    while (i < clients->size())
    {
	if ((*clients)[i]->getType() == EDITOR)
	    return (1);
	i++;
    }
    return (0);
}

void					receiveAndProcess(char (*buff)[1024], std::vector<Client*> *clients, int i)
{
    int					nbRead;

    memset(*buff, 0, 1024);
    if ((nbRead = (*clients)[i]->getSocket()->receive(*buff, 1024)) == 0)
    {
	std::cout << "Client left : " << (*clients)[i]->getName() << std::endl;	    
	ejectClient(clients, i);
    }
    (*buff)[nbRead] = 0;
    if (std::string(*buff).size() > 7 && std::string(*buff).compare(0, 7, "player|") == 0)
    {
	std::cout << "Player " << std::string(*buff).substr(7, std::string(*buff).length()) << " online." << std::endl;
	(*clients)[i]->setName(std::string(*buff).substr(7, std::string(*buff).length()));
	(*clients)[i]->setType(PLAYER);
    }
    else if (editorIsOnline(clients) == 0 && std::string(*buff).size() > 7 && std::string(*buff).compare(0, 7, "editor|") == 0)
    {
	std::cout << "Editor online" << std::endl;
	(*clients)[i]->setName(std::string(*buff).substr(7, std::string(*buff).length()));
	(*clients)[i]->setType(EDITOR);
    }
    if ((*clients)[i]->getName() == "" && (*clients)[i]->getType() == UNDEFINED)
    {
	(*clients)[i]->getSocket()->send("kick", 4);
	ejectClient(clients, i);
    }
}

int					main(int ac, char **av) {
    FDSet				fdSet;
    SocketTCPServer			server;
    std::vector<Client*>		clients;
    int					i;
    int					j;
    char				buff[1024];
    struct timeval			tv;
    int					ret;
    
    if ((ret = init(ac, av, &server)) != 0)
	return (ret);
    while (true)
    {
	fdSet.zero();
	fdSet.set(&server);
	i = 0;
	while (i < clients.size())
	    fdSet.set(clients[i++]->getSocket());
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if (!Select::call(&fdSet, NULL, &tv))
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
		receiveAndProcess(&buff, &clients, i);
		if (clients[j]->getType() == EDITOR)
		{
		    j = 0;
		    while (j < clients.size())
		    {
			if (clients[j]->getType() != EDITOR)
			    clients[j]->getSocket()->send(buff, std::string(buff).size());
			j++;
		    }
		}
	    }
	    i++;
	}
    }
//    SocketTCP::stop();
}
