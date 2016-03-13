#ifndef			IFDSET_HPP_
# define		IFDSET_HPP_

# include		"../../SocketTCP.hpp"

class			IFDSet
{
public:

  virtual ~IFDSet() {}

  virtual void		zero() = 0;
  virtual void		clear(SocketTCP* socketTCP) = 0;
  virtual void		set(SocketTCP* socketTCP) = 0;
  virtual void		set(int fd) = 0;
  virtual int		isset(SocketTCP* socketTCP) = 0;
  virtual int		isset(int fd) = 0;

  virtual const void*	getFDSet() const = 0;
  virtual int		getHighFD() const = 0;
};

#endif			// !IFDSET_HPP_
