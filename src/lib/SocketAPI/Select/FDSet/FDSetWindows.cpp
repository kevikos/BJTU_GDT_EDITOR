#include	"FDSetWindows.hpp"

FDSetWindows::FDSetWindows()
{
}

FDSetWindows::~FDSetWindows()
{
}


void		FDSetWindows::zero()
{
  FD_ZERO(&this->_fdSet);
}

void		FDSetWindows::clear(SocketTCP* socketTCP)
{
  FD_CLR(*(SOCKET*)socketTCP->getSocket(), &this->_fdSet);
}

void		FDSetWindows::set(SocketTCP* socketTCP)
{
  FD_SET(*(SOCKET*)socketTCP->getSocket(), &this->_fdSet);
}

void		FDSetWindows::set(int fd)
{
  FD_SET(fd, &this->_fdSet);
}

int		FDSetWindows::isset(SocketTCP* socketTCP)
{
  int		result;
	
  result = FD_ISSET(*(SOCKET*)socketTCP->getSocket(), &this->_fdSet);
  return (result);
}

int		FDSetWindows::isset(int fd)
{
  int result;

  result = FD_ISSET(fd, &this->_fdSet);
  return (result);
}

const void*	FDSetWindows::getFDSet() const
{
  return (&this->_fdSet);
}

int		FDSetWindows::getHighFD() const
{
  return (this->_highFD);
}
