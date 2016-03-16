#include        <stdlib.h>
#include        <string.h>
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

void		Client::show()
{
    std::cout << "Name: " << _name << std::endl;
    if (_type == PLAYER)
	std::cout << "PLAYER" << std::endl;
    else if (_type == EDITOR)
	std::cout << "EDITOR" << std::endl;
    else
	std::cout << "UNDEFINED" << std::endl;
}
