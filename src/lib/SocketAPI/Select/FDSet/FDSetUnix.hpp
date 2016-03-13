#ifndef			FDSETUNIX_HPP_
# define		FDSETUNIX_HPP_

# include		<sys/select.h>
# include		"IFDSet.hpp"

class			FDSetUnix : public IFDSet
{
public:

  FDSetUnix();
  virtual ~FDSetUnix();

  virtual void		zero();
  virtual void		clear(SocketTCP* socketTCP);
  virtual void		set(SocketTCP* socketTCP);
  virtual void		set(int fd);
  virtual int		isset(SocketTCP* socketTCP);
  virtual int		isset(int fd);

  virtual const void*	getFDSet() const;
  virtual int		getHighFD() const;

private:

  fd_set		_fdSet;
  int			_highFD;
};

#endif			// !FDSETUNIX_HPP_
