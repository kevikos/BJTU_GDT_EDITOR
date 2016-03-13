#include	<iostream>
#include	"FDSet.hpp"

#ifdef		WIN32
#include	"FDSetWindows.hpp"
#else
#include	"FDSetUnix.hpp"
#endif		// WIN32

FDSet::FDSet()
{
#ifdef WIN32
  this->_fdSet = new FDSetWindows;
#else
  this->_fdSet = new FDSetUnix;
#endif // WIN
}

FDSet::~FDSet()
{
  std::cout << "delete fdset" << std::endl;
  delete (this->_fdSet);
}

void		FDSet::clear(SocketTCP* socketTCP)
{
  this->_fdSet->clear(socketTCP);
}

void		FDSet::set(int fd)
{
  this->_fdSet->set(fd);
}

void		FDSet::set(SocketTCP* socketTCP)
{
  this->_fdSet->set(socketTCP);
}

void		FDSet::zero()
{
  this->_fdSet->zero();
}

int		FDSet::isset(SocketTCP* socketTCP)
{
  int	result;

  result = this->_fdSet->isset(socketTCP);
  return (result);
}

int		FDSet::isset(int fd)
{
  int	result;

  result = this->_fdSet->isset(fd);
  return (result);
}

const void*	FDSet::getFDSet() const
{
  return (this->_fdSet->getFDSet());
}

int		FDSet::getHighFD() const
{
  return (this->_fdSet->getHighFD());
}
