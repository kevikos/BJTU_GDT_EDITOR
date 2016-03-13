#ifndef				SOCKETTCPUNIX_HPP_
# define			SOCKETTCPUNIX_HPP_

# include			"ISocketTCP.hpp"

class				SocketTCPUnix : public ISocketTCP
{
public:

  SocketTCPUnix();
  virtual ~SocketTCPUnix();

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

  int				_socket;
  std::string			_ip;
};

#endif				// !SOCKETTCPUNIX_HPP_
