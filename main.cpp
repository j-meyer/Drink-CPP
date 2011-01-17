//	main.cpp
//	Author: McLovin
//	Just starts the server

#include "sunday.h"
#include <stdlib.h>
#include <time.h>

/*!\brief Main method, creates and runs a server for each drink machine.
 * \param argc the number of arguments
 * \param argv an array of character arrays, the input
 *
 * Seeds random, then creates and starts a SundayServer for each machine.
 */
int main ( int argc, char* argv[] )
{
    srand ( time ( NULL ) );
    ///\todo Might change this to have the machine name specified by a
    ///config file or a command line switch.
    SundayServer server = SundayServer ( "BD" );
    server.startServer();
}

