#include		<iostream>
#include		"SocketTCPServer.hpp"

SocketTCPServer::SocketTCPServer()
{
  std::cout << "Creation de la SocketTCPServer." << std::endl;
}

SocketTCPServer::~SocketTCPServer()
{
}

bool			SocketTCPServer::create(const std::string& listenHost, int listenPort)
{
  if (this->_socketTCP->xSocket() == false)
    {
      std::cerr << "[ERROR] : SocketTCP::xSocket failed." << std::endl;
      return (false);
    }
  if (this->_socketTCP->xBind(listenHost, listenPort) == false)
    {
      std::cerr << "[ERROR] : SocketTCP::xBind failed." << std::endl;
      return (false);
    }
  if (this->_socketTCP->xListen(42) == false)
    {
      std::cerr << "[ERROR] : SocketTCP::xListen failed." << std::endl;
      return (false);
    }
  return (true);
}

SocketTCPClient*	SocketTCPServer::acceptClient()
{
  ISocketTCP*		socketTCP;
  SocketTCPClient*	socketTCPClient;

  if ((socketTCP = this->_socketTCP->xAccept()) == NULL)
    {
      std::cerr << "[ERROR] : SocketTCP::xAccept failed." << std::endl;
      return (NULL);
    }
  socketTCPClient = new SocketTCPClient;
  socketTCPClient->setSocketTCP(socketTCP);
  return (socketTCPClient);
}
