#ifndef			FDSETWINDOWS_HPP_
# define		FDSETWINDOWS_HPP_

# include		<WinSock2.h>
# include		"IFDSet.hpp"

class			FDSetWindows : public IFDSet
{
public:

  FDSetWindows();
  virtual ~FDSetWindows();

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

#endif			// !FDSETWINDOWS_HPP_
