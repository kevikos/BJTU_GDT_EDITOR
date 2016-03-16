#include	"Server.hpp"
#include	"Client.hpp"

Client::Client(SocketTCPClient* socket)
{
    _socket = socket;
    _name = "";
    _type = UNDEFINED;
}

Client::~Client()
{
}

void		Client::setName(std::string name)
{
    _name = name;
}

std::string	Client::getName()
{
    return (_name);
}

void		Client::setType(ClientType type)
{
    _type = type;
}

ClientType	Client::getType()
{
    return (_type);
}

SocketTCPClient*	Client::getSocket()
{
    return (_socket);
}
