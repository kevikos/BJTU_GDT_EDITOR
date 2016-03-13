#ifndef				ISOCKETTCP_HPP_
# define			ISOCKETTCP_HPP_

# include			<string>

class				ISocketTCP
{
public:

  virtual ~ISocketTCP() {}

  virtual bool			start() = 0;
  virtual bool			stop() = 0;

  virtual ISocketTCP*		xAccept() = 0;
  virtual bool			xBind(const std::string& host, int port) = 0;
  virtual bool			xConnect(const std::string& host, int port) = 0;
  virtual bool			xSocket() = 0;
  virtual bool			xListen(int queueSize) = 0;
  virtual int			xRecv(void* buf, int len) = 0;
  virtual int			xSend(const void* buf, int len) = 0;
  virtual bool			xClose() = 0;

  virtual const void*		getSocket() const = 0;
  virtual const std::string&	getIp() const = 0;
};

#endif				// !ISOCKETTCP_HPP_
