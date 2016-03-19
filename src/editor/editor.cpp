#include			<iostream>
#include			<stdlib.h>
#include			<string.h>
#include			"../lib/SocketAPI/SocketTCPClient.hpp"
#include			"../lib/SocketAPI/Select/FDSet/FDSet.hpp"
#include			"../lib/SocketAPI/Select/Select.hpp"

int				main(int ac, char **av) {
    SocketTCPClient		client;
    FDSet			fdSet;
    char			buff[1024];
    std::string			entry;
    int				nbRead;

    if (ac != 3)
    {
	std::cout << "./editor host port" << std::endl;
	return (0);
    }
    client.start();
    client.connectToServer(av[1], atoi(av[2]));
    while (true)
    {
        fdSet.zero();
        fdSet.set(&client);
        fdSet.set(0);
        if (!Select::call(&fdSet, NULL, NULL))
	{
	    std::cout << "Editor : Socket managment failed" << std::endl;
	    return (-1);
	}
        if (fdSet.isset(&client))
        {
            memset(buff, 0, 1024);
            if ((nbRead = client.receive(buff, 1024)) == 0)
            {
                client.close();
                std::cout << "Server left" << std::endl;
                return 0;
            }
	    buff[nbRead] = 0;
            if (std::string(buff) == "BIENVENU")
            {
                client.send("editor|editor", 13);
            }
            if (std::string(buff) == "kick")
            {
                std::cout << "You are kicked by server" << std::endl;
                return (0);
            }
        }
        if (fdSet.isset(0))
        {
            std::getline(std::cin, entry);
            client.send(entry.c_str(), entry.length());
        }      
    }
}
