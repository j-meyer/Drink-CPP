//	sunday.cpp
//	Author: McLovin
//	Implements the Sunday protocol to interface with drink
//	URL for protocol:
//  http://web.archive.org/web/20050207222128/antiduh.com/drink/docs/sunday-protocol.html
//

#include "sunday.h"
#include "command.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>

/*! \brief SundayServer Constructor
 * \param machineName - The machine name (BigDrink, LittleDrink, Snack, etc.)
 * Create and bind the socket and set it to listen
 *
 */
SundayServer::SundayServer ( std::string machineName )
{
    struct  sockaddr_in server; // server's IP address
    userCount = 0;
    machine = machineName;
    //Create the socket
    sock = socket ( AF_INET, SOCK_STREAM, 0 );
    if ( sock < 0 )
    {
        std::cerr << "socket: " << strerror ( errno ) << std::endl;
        exit ( EXIT_FAILURE );
    }

    //Set all the settings for the socket
    bzero ( &server, sizeof ( server ) );
    server.sin_family = AF_INET;
    server.sin_port =  htons ( portNumber );

    //If the bind fails, die
    if (
        bind ( sock, ( struct sockaddr * ) &server, sizeof ( server ) ) < 0
    )
    {
        std::cerr << "Binding Failed " << std::endl;
        exit ( EXIT_FAILURE );
    }

    //set the socket to listen
    if ( listen ( sock, 1 ) < 0 )
    {
        std::cerr << "listen: " << strerror ( errno ) << std::endl;
        exit ( EXIT_FAILURE );
    }
}
/*!\brief Starts the server
 * \return void
 *Listens for connections, upon getting one, hand it off
 *to be handled by handleClient.
 */
void SundayServer::startServer()
{
    bool keepRunning = true;
    while ( keepRunning )
    {
#ifdef DEBUG
        std::cout << "Waiting for a connection ..." << std::endl;
#endif
        ///\todo start a timer once connected so we can kick someone off
        // 		/*after 1 minute of not touching anything
        //On accept: fork
        int acceptedSock = accept ( sock, 0, 0 );
        pid_t pID = fork();
        if ( pID ==0 )  //Then we are the child, so pass off
        {
            handleClient ( acceptedSock );
            exit ( 0 );//avoids zombies by shooting them in the head
        }
        else
        {
            userCount += 1;
        }
    }//while(keepRunning)
}
/*!Handles reading and writing to the client, called once a connection is
 *accepted
 */
int SundayServer::handleClient ( int acceptedSock )
{
    char buf[512];   // data buffer
    int len;        // buffer length
    const char *banner = "Welcome to Drink!\n";
    int sendCheck;//int used to make sure all the data is sent
    Command commandInterpreter = Command ( userCount, machine, acceptedSock );
    //check to make sure accepted socket is valid
    if ( acceptedSock < 0 )
    {
        return acceptedSock;
    }
#ifdef DEBUG
    std::cout << "Connected to client " << std::endl;
#endif

    //Send Banner to Client
    sendCheck = send ( acceptedSock, banner, strlen ( banner ),0 );
    if ( sendCheck < 0 )
    {
        std::cerr << "write: " << strerror ( errno ) << std::endl;
        exit ( EXIT_FAILURE );
    }
    // Now read and respond to messages until end of file is
    // reached (which means the client closed the connection).
    len = read ( acceptedSock, buf, sizeof ( buf ) );
#ifdef DEBUG
    std::cout << "length of message: " << len << std::endl;
#endif

    while ( len > 0 )
    {
#ifdef DEBUG
        std::cout << "interpret command" << std::endl;
#endif
        //if the user put in quit as the command, return
        //because we're done
        if ( commandInterpreter.interpretCommand ( buf, len ) == -1 )
        {
            return 0;
        }
        else
        {
            len = read ( acceptedSock, buf, sizeof ( buf ) );
        }
    }

    if ( len < 0 )
    {
        std::cerr << "read: " << strerror ( errno ) << std::endl;
        exit ( EXIT_FAILURE );
    }
    close ( acceptedSock );
    return 0;
}
