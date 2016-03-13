#include	<sys/select.h>
#include	"FDSetUnix.hpp"

FDSetUnix::FDSetUnix()
{
  this->_highFD = 0;
}

FDSetUnix::~FDSetUnix()
{
}

void		FDSetUnix::zero()
{
  this->_highFD = 0;
  FD_ZERO(&this->_fdSet);
}

void		FDSetUnix::clear(SocketTCP *socketTCP)
{
  FD_CLR(*(int*)socketTCP->getSocket(), &this->_fdSet);
}

void		FDSetUnix::set(SocketTCP *socketTCP)
{
  if (*(int*)socketTCP->getSocket() > this->_highFD)
    this->_highFD = *(int*)socketTCP->getSocket();
  FD_SET(*(int*)socketTCP->getSocket(), &this->_fdSet);
}

void		FDSetUnix::set(int fd)
{
  FD_SET(fd, &this->_fdSet);
}

int		FDSetUnix::isset(SocketTCP *socketTCP)
{
  int		result;

  result = FD_ISSET(*(int*)socketTCP->getSocket(), &this->_fdSet);
  return (result);
}

int		FDSetUnix::isset(int fd)
{
  int		result;

  result = FD_ISSET(fd, &this->_fdSet);
  return (result);
}

const void*	FDSetUnix::getFDSet() const
{
  return (&this->_fdSet);
}

int		FDSetUnix::getHighFD() const
{
  return (this->_highFD);
}
