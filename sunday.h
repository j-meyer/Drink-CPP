#ifndef SUNDAY_HEADER
#define SUNDAY_HEADER
#include "command.h"
#include "controller.h"
#include <vector>
#include <string>
///There is one sunday server instantiated for each drink machine there is.
class SundayServer
{
public:
    /*! Creates a server, machine is the machine name
     *(BD, LD, or Snack) controller is a reference to the one
     *controller used for
     *everything
     */
    SundayServer ( std::string machine );
    /*! Actually starts the server
     */
    void startServer();
private:
    ///port number to use
    static const int portNumber = 4242;
    ///the number of users so far that have connected
    int userCount;
    ///the machine's name
    std::string machine;
    ///the file descriptor for the socket
    int sock;
    ///called when a socket is accepted
    int handleClient ( int acceptedSock );
    ///tokenizes the arg by whitespace and returns it in a vector
    std::vector<std::string> tokenize ( char arg[], int length );
};
#endif
///\todo Kick idler off if on for more than a minute
/*
Commands:
	acctmgrchk
	chpass
	code
	drop
	getbalance
	location
	pass
	quit
	rand
	stat
	temp
	user
	whoami - return username if logged in, error else
	version
	-------------
	|admin only:|
	-------------
	addcredits
	adduser
	chpass
	editslot
	edituser
	getbalance
	isvaliduser
	log
	queryadmin
	rmuser
	setadmin
	shutdown



*/






