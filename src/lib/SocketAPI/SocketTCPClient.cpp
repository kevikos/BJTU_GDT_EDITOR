#include	<iostream>
#include	"SocketTCPClient.hpp"

SocketTCPClient::SocketTCPClient()
{
  std::cout << "Creation de la SocketTCPClient." << std::endl;
}

SocketTCPClient::~SocketTCPClient()
{

}

bool		SocketTCPClient::connectToServer(const std::string& host, int port)
{
  if (this->_socketTCP->xSocket() == false)
    {
      std::cerr << "[ERROR] : SocketTCP::xSocket failed." << std::endl;
      return (false);
    }
  if (this->_socketTCP->xConnect(host, port) == false)
    {
      std::cerr << "[ERROR] : SocketTCP::xConnect failed." << std::endl;
      return (false);
    }
  return (true);
}

int		SocketTCPClient::send(const void* buf, int len)
{
  int		result;

  if ((result = this->_socketTCP->xSend(buf, len)) == -1)
    {
      std::cerr << "[ERROR] : SocketTCP::xSend failed." << std::endl;
    }
  return (result);
}

int		SocketTCPClient::receive(void* buf, int len)
{
  int		result;

  if ((result = this->_socketTCP->xRecv(buf, len)) == -1)
    {
      std::cerr << "[ERROR] : SocketTCP::xRecv failed." << std::endl;
    }
  return (result);
}

void		SocketTCPClient::setSocketTCP(ISocketTCP* socketTCP)
{
  delete (this->_socketTCP);
  this->_socketTCP = socketTCP;
}
