#include		<sys/types.h> 
#include		<sys/socket.h>
#include		<arpa/inet.h>
#include		<netdb.h>
#include		<cstdlib>
#include		<unistd.h>
#include		"SocketTCPUnix.hpp"

SocketTCPUnix::SocketTCPUnix()
{
}

SocketTCPUnix::~SocketTCPUnix()
{
}

bool			SocketTCPUnix::start()
{
  return (true);
}

bool			SocketTCPUnix::stop()
{
  return (true);
}

ISocketTCP*		SocketTCPUnix::xAccept()
{
  int			clientAddrLen;
  sockaddr_in		clientAddr;
  int			socket;

  clientAddrLen = sizeof(clientAddr);
  if ((socket = accept(this->_socket, (sockaddr*)&clientAddr, (socklen_t*)&clientAddrLen)) == -1)
    {
      return (NULL);
    }
  SocketTCPUnix* client = new SocketTCPUnix;
  client->_socket = socket;
  client->_ip = inet_ntoa(clientAddr.sin_addr);
  return (client);
}

bool			SocketTCPUnix::xBind(const std::string& host, int port)
{
  sockaddr_in		servAddr;

  (void)host;
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = INADDR_ANY;
  servAddr.sin_port = htons(port);
  if ((bind(this->_socket, (sockaddr*)&servAddr, sizeof(servAddr))) != 0)
    {
      return (false);
    }
  return (true);
}

bool			SocketTCPUnix::xConnect(const std::string& host, int port)
{
  sockaddr_in		servAddr;

  servAddr.sin_family = AF_INET;
  if ((servAddr.sin_addr.s_addr = inet_addr(host.c_str())) == INADDR_NONE)
    {
      return (false);
    }
  servAddr.sin_port = htons(port);
  if ((connect(this->_socket, (sockaddr*)&servAddr, sizeof(servAddr))) != 0)
    {
      return (false);
    }
  return (true);
}

bool			SocketTCPUnix::xSocket()
{
  protoent*		proto;

  if ((proto = getprotobyname("TCP")) == NULL)
    {
      return (false);
    }
  if ((this->_socket = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    {
      return (false);
    }
  return (true);
}

bool			SocketTCPUnix::xListen(int queueSize)
{
  if ((listen(this->_socket, queueSize)) != 0)
    {
      return (false);
    }
  return (true);
}

int			SocketTCPUnix::xRecv(void* buf, int len)
{
  int			result;

  result = recv(this->_socket, buf, len, 0);
  return (result);
}

int			SocketTCPUnix::xSend(const void* buf, int len)
{
  int			result;

  result = send(this->_socket, buf, len, 0);
  return (result);
}

bool			SocketTCPUnix::xClose()
{
  if (close(this->_socket) != 0)
    {
      return (false);
    }
  return (true);
}

const void*		SocketTCPUnix::getSocket() const
{
  return (&this->_socket);
}

const std::string&	SocketTCPUnix::getIp() const
{
  return (this->_ip);
}
