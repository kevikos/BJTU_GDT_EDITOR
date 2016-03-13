#include <iostream>
#include "../lib/SocketAPI/SocketTCPClient.hpp"
#include "../lib/SocketAPI/Select/FDSet/FDSet.hpp"
#include "../lib/SocketAPI/Select/Select.hpp"

int main(int ac, char **av) {
  SocketTCPClient client;

  if (ac != 3)
    {
      std::cout << "./client host port" << std::endl;
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
	  std::cout << "msg : " << buff << std::endl;
	  memset(buff, 0, 1024);
	}
      if (fdSet.isset(0))
	{
	  std::getline(std::cin, entry);
	  //	  std::cin >> entry;
	  //std::cout << "Send : " << entry << std::endl;
	  client.send(entry.c_str(), entry.length());
	}      
    }
}
