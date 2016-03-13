#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "../lib/SocketAPI/SocketTCP.hpp"
#include "../lib/SocketAPI/SocketTCPServer.hpp"
#include "../lib/SocketAPI/Select/FDSet/FDSet.hpp"
#include "../lib/SocketAPI/Select/Select.hpp"

//using namespace std;

int main(int ac, char **av) {
  FDSet fdSet;
  SocketTCPServer server;
  std::vector<SocketTCPClient*> clients;
  int i;
  int j;
  char buff[1024];
  int nbRead;

  if (ac != 2)
    {
      std::cout << "./server port" << std::endl;
      return (0);
    }
  SocketTCP::start();
  server.create("127.0.0.1", atoi(av[1]));
  while (true)
    {
      usleep(1);
      fdSet.zero();
      fdSet.set(&server);
      i = 0;
      while (i < clients.size())
	{
	  fdSet.set(clients[i]);
	  i++;
	}
      Select::call(&fdSet, NULL);
      if (fdSet.isset(&server))
	{
	  SocketTCPClient* tmp = server.acceptClient();
	  clients.push_back(tmp);
	}
      i = 0;
      while (i < clients.size())
	{
	  if (fdSet.isset(clients[i]))
	    {
	      
	      memset(buff, 0, 1024);
	      if ((nbRead = clients[i]->receive(buff, 1024)) == 0)
		{
		  buff[nbRead] = 0;
		  clients[i]->close();
		  delete clients[i];
		  clients.erase(clients.begin() + i);
		}
	      j = 0;
	      while (j < clients.size())
		{
		  if (j != i)
		    {
		      std::cout << "SEND : " << buff << std::endl;
		    clients[j]->send(buff, nbRead);
		    }
		  j++;
		}
	    }
	  i++;
	}
    }
  SocketTCP::stop();
}
