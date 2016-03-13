#ifndef		SOCKETTCPCLIENT_HPP_
# define	SOCKETTCPCLIENT_HPP_

# include	"SocketTCP.hpp"

class		SocketTCPClient : public SocketTCP
{
 public:

  SocketTCPClient();
  virtual ~SocketTCPClient();

  bool		connectToServer(const std::string& host, int port);
  int		send(const void* buf, int len);
  int		receive(void* buf, int len);

  void		setSocketTCP(ISocketTCP* socketTCP);
};


#endif		// !SOCKETTCPCLIENT_HPP_
