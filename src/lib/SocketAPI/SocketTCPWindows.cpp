#include		<iostream>
#include		"SocketTCPWindows.hpp"

#pragma comment(lib, "Ws2_32.lib")

SocketTCPWindows::SocketTCPWindows()
{
}

SocketTCPWindows::~SocketTCPWindows()
{
}

bool			SocketTCPWindows::start()
{
  WSADATA		wsaData;

  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
      return (false);
    }
  return (true);
}

bool			SocketTCPWindows::stop()
{
  if (WSACleanup() != 0)
    {
      return (false);
    }
  return (true);
}

ISocketTCP*		SocketTCPWindows::xAccept()
{
  int			clientAddrLen;
  sockaddr_in		clientAddr;
  SOCKET		socket;

  clientAddrLen = sizeof(clientAddr);
  if ((socket = WSAAccept(this->_socket, (sockaddr*)&clientAddr, &clientAddrLen, NULL, NULL)) == INVALID_SOCKET)
    {
      return (NULL);
    }
  SocketTCPWindows *client = new SocketTCPWindows;
  this->_ip = inet_ntoa(clientAddr.sin_addr);
  client->_socket = socket;
  return (client);
}

bool			SocketTCPWindows::xBind(const std::string& host, int port)
{
  sockaddr_in		servAddr;

  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = INADDR_ANY;
  servAddr.sin_port = htons(port);
  if ((bind(this->_socket, (sockaddr*)&servAddr, sizeof(servAddr))) != 0)
    {
      return (false);
    }
  return (true);
}

bool			SocketTCPWindows::xConnect(const std::string& host, int port)
{
  sockaddr_in		servAddr;

  servAddr.sin_family = AF_INET;
  if ((servAddr.sin_addr.s_addr = inet_addr(host.c_str())) == INADDR_NONE)
    {
      return (false);
    }
  servAddr.sin_port = htons(port);
  if ((WSAConnect(this->_socket, (sockaddr*)&servAddr, sizeof(servAddr), NULL, NULL, NULL, NULL)) != 0)
    {
      return (false);
    }
  return (true);
}

bool			SocketTCPWindows::xSocket()
{
  protoent*		proto;

  if ((proto = getprotobyname("TCP")) == NULL)
    {
      return (false);
    }
  if ((this->_socket = WSASocket(AF_INET, SOCK_STREAM, proto->p_proto, NULL, NULL, NULL)) == INVALID_SOCKET)
    {
      return (false);
    }
  return (true);
}

bool			SocketTCPWindows::xListen(int queueSize)
{
  if ((listen(this->_socket, queueSize)) != 0)
    {
      return (false);
    }
  return (true);
}

int			SocketTCPWindows::xRecv(void* buf, int len)
{
  WSABUF		wsabuf;
  int			flags;
  int			bytesRecv;

  flags = 0;
  wsabuf.buf = (char*)buf;
  wsabuf.len = len;
  WSARecv(this->_socket, &wsabuf, 1, (LPDWORD)&bytesRecv, (LPDWORD)&flags, NULL, NULL);
  return (bytesRecv);
}

int			SocketTCPWindows::xSend(const void* buf, int len)
{
  WSABUF		wsabuf;
  int			bytesSend;

  wsabuf.buf = (char*)buf;
  wsabuf.len = len;
  WSASend(this->_socket, &wsabuf, 1, (LPDWORD)&bytesSend, 0, NULL, NULL);
  return (bytesSend);
}

bool			SocketTCPWindows::xClose()
{
  if (closesocket(this->_socket) != 0)
    {
      return (false);
    }
  return (true);
}

const void*		SocketTCPWindows::getSocket() const
{
  return (&this->_socket);
}

const std::string&	SocketTCPWindows::getIp() const
{
  return (this->_ip);
}
