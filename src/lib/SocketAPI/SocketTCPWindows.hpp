#ifndef				SOCKETTCPWINDOWS_HPP_
# define			SOCKETTCPWINDOWS_HPP_

# define			_WINSOCK_DEPRECATED_NO_WARNINGS

# include			<WinSock2.h>
# include			"ISocketTCP.hpp"

class				SocketTCPWindows : public ISocketTCP
{
public:
 
  SocketTCPWindows();
  virtual ~SocketTCPWindows();

  virtual bool			start();
  virtual bool			stop();

  virtual ISocketTCP*		xAccept();
  virtual bool			xBind(const std::string& host, int port);
  virtual bool			xConnect(const std::string& host, int port);
  virtual bool			xSocket();
  virtual bool			xListen(int queueSize);
  virtual int			xRecv(void* buf, int len);
  virtual int			xSend(const void* buf, int len);
  virtual bool			xClose();

  virtual const void*		getSocket() const;
  virtual const std::string&	getIp() const;

private:

  SOCKET			_socket;
  std::string			_ip;
};

#endif				// !SOCKETTCPWINDOWS_HPP_
