#ifndef COMMAND_HEADER
#define COMMAND_HEADER
#include <vector>
#include <string>
#include "controller.h"
#ifdef DEBUG
#include <iostream>
#endif

/*!\brief Command class, one instance for each user.
 *
 * The command class is basically an instantiated user, it keeps track of the
 * username, password, and handles all the commands that a user might issue. All
 * functions assume that the first token in the vector passed to it is correct
 * and any/all additional tokens in the vector may be dirty. Anything returning
 * an error as an int will take the error message, as specified in the SUNDAY
 * protocol and negate it. Success is specified by a 0.
 */
class Command
{
		//let SundayServer grab access to all the functions
		friend class SundayServer;
	public:
		Command ( int num, std::string machineName, int acceptedSock );
		int interpretCommand ( char command[], int length );
		///\todo switch to private
	public:
		//instance shit
		///The socket
		int acceptedSocket;
		///The user's username
		std::string username;
		///The user's password
		std::string password;
		///The machine the user is currently connected to
		std::string machine;
		///Whether or not the user is authenticated
		bool authenticated;
		///Whether or not the user is an admin
		bool admin;
		//end of instance shit
		std::vector<std::string> tokenize ( char arg[], int length );
		///References the one and only controller
		Controller * control;
		///user number that is currently connected
		int userNum;
		
		//All the functions:
		int unknowncommand ();
		//returns -10 on an unknown command
		//all the commands, we have to deal with
		int acctmgrchk ( std::vector<std::string> commands );
		int chpass ( std::vector<std::string> commands );
		int code ( std::vector<std::string> commands );
		int drop ( std::vector<std::string> commands );
		int getbalance ( std::vector<std::string> commands );
		int location ( std::vector<std::string> commands );
		int pass ( std::vector<std::string> commands );
		int quit ( std::vector<std::string> commands );
		int rand ( std::vector<std::string> commands );
		int stat ( std::vector<std::string> commands );
		int temp ( std::vector<std::string> commands );
		int user ( std::vector<std::string> commands );
		int whoami ( std::vector<std::string> commands );
		int version ( std::vector<std::string> commands );
		//All these are admin commands
		int addcredits ( std::vector<std::string> commands );
		int adduser ( std::vector<std::string> commands );
		int editslot ( std::vector<std::string> commands );
		int edituser ( std::vector<std::string> commands );
		int isvaliduser ( std::vector<std::string> commands );
		int log ( std::vector<std::string> commands );
		int queryadmin ( std::vector<std::string> commands );
		int rmuser ( std::vector<std::string> commands );
		int setadmin ( std::vector<std::string> commands );
		int shutdown ( std::vector<std::string> commands );
		void sendMessage(std::string message);
		int sendMessage(int errorNum);
};
#endif
