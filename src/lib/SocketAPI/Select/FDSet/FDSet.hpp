#ifndef		FDSET_HPP_
# define	FDSET_HPP_

# include	"IFDSet.hpp"

class		FDSet
{
public:

  FDSet();
  ~FDSet();

  void		zero();
  void		clear(SocketTCP* socketTCP);
  void		set(SocketTCP* socketTCP);
  void		set(int fd);
  int		isset(SocketTCP* socketTCP);
  int		isset(int fd);

  const void*	getFDSet() const;
  int		getHighFD() const;

private:

  IFDSet*	_fdSet;
};

#endif		// !FDSET_HPP_
