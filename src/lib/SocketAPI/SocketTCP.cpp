#include		<iostream>
#include		"SocketTCP.hpp"

#ifdef			WIN32
#include		"SocketTCPWindows.hpp"
#else
#include		"SocketTCPUnix.hpp"
#endif			// WIN32

SocketTCP::SocketTCP()
{
#ifdef WIN32
  this->_socketTCP = new SocketTCPWindows;
#else
  this->_socketTCP = new SocketTCPUnix;
#endif // WIN
}

SocketTCP::~SocketTCP()
{
  delete this->_socketTCP;
}

bool			SocketTCP::start()
{
  ISocketTCP*		socketTCP;

#ifdef WIN32
  socketTCP = new SocketTCPWindows;
#else
  socketTCP = new SocketTCPUnix;
#endif // WIN
  if (socketTCP->start() == false)
    {
      std::cout << "[ERROR] : SocketTCP::start failed." << std::endl;
      delete (socketTCP);
      return (false);
    }
  delete (socketTCP);
  return (true);
}

bool			SocketTCP::stop()
{
  ISocketTCP*		socketTCP;

#ifdef WIN32
  socketTCP = new SocketTCPWindows;
#else
  socketTCP = new SocketTCPUnix;
#endif // WIN
  if (socketTCP->stop() == false)
    {
      std::cout << "[ERROR] : SocketTCP::stop failed." << std::endl;
      delete (socketTCP);
      return (false);
    }
  delete (socketTCP);
  return (true);
}

bool			SocketTCP::close()
{
  if (this->_socketTCP->xClose() == false)
    {
      std::cerr << "[ERROR] : SocketTCP::xClose failed." << std::endl;
      return (false);
    }
  return (true);
}

const void*		SocketTCP::getSocket() const
{
  return (this->_socketTCP->getSocket());
}

const std::string&	SocketTCP::getIp() const
{
  return (this->_socketTCP->getIp());
}
