#include <iostream>
#include "../lib/SocketAPI/SocketTCPClient.hpp"
#include "../lib/SocketAPI/Select/FDSet/FDSet.hpp"
#include "../lib/SocketAPI/Select/Select.hpp"

int main(int ac, char **av) {
    SocketTCPClient client;

    if (ac != 4)
    {
	std::cout << "./client host port name" << std::endl;
	return (0);
    }
    client.start();
    client.connectToServer(av[1], atoi(av[2]));


    FDSet fdSet;
    char buff[1024];
    std::string entry;
    int nbRead;

    while (true)
    {
	fdSet.zero();
	fdSet.set(&client);
	fdSet.set(0);
	Select::call(&fdSet, NULL);
	if (fdSet.isset(&client))
	{
	    if ((nbRead = client.receive(buff, 1024)) == 0)
	    {
		client.close();
		std::cout << "Server left" << std::endl;
		return 0;
	    }
	    if (std::string(buff) == "BIENVENU")
	    {
		client.send(("player|" + std::string(av[3])).c_str(), 7 + std::string(av[3]).length());
	    }
	    if (std::string(buff) == "kick")
	    {
		std::cout << "You are kicked by server" << std::endl;
		return (0);
	    }
	    std::cout << "msg : " << buff << std::endl;
	    memset(buff, 0, 1024);
	}
	if (fdSet.isset(0))
	{
	    std::getline(std::cin, entry);
	    client.send(entry.c_str(), entry.length());
	}      
    }
}
