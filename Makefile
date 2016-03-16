CC		=	g++ -g

RM		=	rm -f

CXXFLAGS	=	##-Wextra -Wall -Werror

LDFLAGS		=	##

SERVERNAME	=	Server

CLIENTNAME	=	Client

EDITORNAME	=	Editor

SRCSERVER	=	./src/server/Server.cpp					\
			./src/server/Client.cpp

SRCCLIENT	=	./src/client/client.cpp

SRCEDITOR	=	./src/editor/editor.cpp

SRCLIBRARY	=	./src/lib/SocketAPI/SocketTCP.cpp			\
			./src/lib/SocketAPI/SocketTCPClient.cpp			\
			./src/lib/SocketAPI/SocketTCPServer.cpp			\
			./src/lib/SocketAPI/SocketTCPUnix.cpp			\
			./src/lib/SocketAPI/Select/Select.cpp			\
			./src/lib/SocketAPI/Select/SelectUnix.cpp		\
			./src/lib/SocketAPI/Select/FDSet/FDSet.cpp		\
			./src/lib/SocketAPI/Select/FDSet/FDSetUnix.cpp

LIBRARYOBJS	=	$(SRCLIBRARY:.cpp=.o)

SERVEROBJS	=	$(SRCSERVER:.cpp=.o)

CLIENTOBJS	=	$(SRCCLIENT:.cpp=.o)

EDITOROBJS	=	$(SRCEDITOR:.cpp=.o)

all:			$(SERVERNAME) $(CLIENTNAME) $(EDITORNAME)

$(SERVERNAME):		$(SERVEROBJS) $(LIBRARYOBJS)
			$(CC) $(SERVEROBJS) $(LIBRARYOBJS) -o $(SERVERNAME)

$(CLIENTNAME):		$(CLIENTOBJS) $(LIBRARYOBJS)
			$(CC) $(CLIENTOBJS) $(LIBRARYOBJS) -o $(CLIENTNAME)

$(EDITORNAME):		$(EDITOROBJS) $(LIBRARYOBJS)
			$(CC) $(EDITOROBJS) $(LIBRARYOBJS) -o $(EDITORNAME)

clean:
			$(RM) $(LIBRARYOBJS) $(SERVEROBJS) $(CLIENTOBJS) $(EDITOROBJS)

fclean:			clean
			$(RM) $(SERVERNAME) $(CLIENTNAME) $(EDITORNAME)

re:			fclean all

.PHONY:			all clean fclean re
