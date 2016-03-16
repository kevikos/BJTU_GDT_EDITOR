#ifndef			CLIENT_HPP_
# define		CLIENT_HPP_
			       
# include		"../ClientTypeEnum.hpp"
# include		"Server.hpp"

class			Client
{
private:

    SocketTCPClient*	_socket;
    std::string		_name;
    ClientType		_type;

public:

    Client(SocketTCPClient*);
    virtual		~Client();
    void		setName(std::string);
    std::string		getName();
    void		setType(ClientType);
    ClientType		getType();
    SocketTCPClient*	getSocket();
    void		show();
};

#endif			/* CLIENT_HPP_ */
