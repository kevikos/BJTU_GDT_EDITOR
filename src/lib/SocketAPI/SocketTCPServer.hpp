#ifndef			SOCKETTCPSERVER_HPP_
# define		SOCKETTCPSERVER_HPP_

# include		<string>
# include		"SocketTCP.hpp"
# include		"SocketTCPClient.hpp"

class			SocketTCPServer : public SocketTCP
{
public:

  SocketTCPServer();
  virtual ~SocketTCPServer();

  bool			create(const std::string& listenHost, int listenPort);
  SocketTCPClient*	acceptClient();
};

#endif			// !SOCKETTCPSERVER_HPP_
