#ifndef			SOCKETTCP_HPP_
# define		SOCKETTCP_HPP_

# include		"ISocketTCP.hpp"

class			SocketTCP
{
public:

  SocketTCP();
  virtual ~SocketTCP();

  static bool		start();
  static bool		stop();

  bool			close();

  const void*		getSocket() const;
  const std::string&	getIp() const;

protected:

  ISocketTCP*		_socketTCP;
};

#endif			// !SOCKETTCP_HPP_
