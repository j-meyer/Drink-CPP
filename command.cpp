//Contains all the fun code that needs to be run when a user actually enters
//in a command
#include "command.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <sstream>
#include <boost/regex.hpp>


/*!\brief Command constructor
 * \param num the user number, not really used for anything right now, might
 * be used as a unique id at some point for certain function calls.
 * \param machineName the name of the machine the user wishes to connect to
 * \param acceptedSock the file descriptor of the socket used
 *
 * Sets all the class variables to false and empty strings.
 */
Command::Command ( int num, int machineName, int acceptedSock )
{
    machine = machineName;
    control = Controller::Instance();
    userNum = num;
#ifdef DEBUG
    std::cout << "Command Constructor " << std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    acceptedSocket = acceptedSock;
    username = "";
    password = "";
    authenticated = false;
    admin = false;
}
//Each of these commands assumes that the first token has already  been verified
//but the subsequent commands need to be checked to make sure they are valid
//and any sort of authentication and verifying that the parameters are correct
//is handled here as well

/*!\brief Writes to the socket that the command was invalid.
 * \return An integer specifying the result (-452)
 */
int Command::unknowncommand ()
{
#ifdef DEBUG
    std::cout << "unknown start"<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    return sendMessage ( 452 );
}
/*!\brief Writes to the socket if the account manager server is running or not.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::acctmgrchk ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "acctmgrchk start"	<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    int responseVal;
    if ( commands.size() == 1 )
    {
        std::string response;
        if ( control->isAvailable() )
        {
            response = "OK Account server subsystem running.";
            responseVal = 0;
        }
        else
        {
            response = control->err->errorMap[350];
            responseVal = 350;
        }
        sendMessage ( response );
        return responseVal;
    }
    else
    {
        return sendMessage ( 406 );
    }
}
/*!\brief Change password.
 * \param commands a vector of strings containing the tokenized commands
 * \return Always returns -451 as we are not planning on implementing this
 */
int Command::chpass ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "chpass start"	<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    //This is not being implemented
    return sendMessage ( 451 );
}
/*!\brief Sets a code on drink to drop free drinks on a certain combo.
 * \param commands a vector of strings containing the tokenized commands
 * \return Always returns -451 as we aren't planning on implementing this
 */
int Command::code ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "code start" << std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    //This is not being implemented
    return sendMessage ( 451 );
}
//DROP <slot index> [delay]
///\todo look at the difference between the valid slots for delayed drop and non delayed drops
/*!\brief Drops a drink.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::drop ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "drop start" << std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    //DROP <slot index> [delay]
    boost::regex numbers ( "[[:digit:]]+" );//"\d+" doesn't work
    if ( !authenticated )
    {
        return sendMessage ( 204 );
    }
    if ( ! boost::regex_match ( commands[1].c_str(), numbers ) )
    {
#ifdef DEBUG
        std::cout << "Line 139 - Regex Failed" << std::endl;
        std::cout << commands[1].c_str() << "*" << std::endl;
#endif
        return sendMessage ( 409 );
    }
    int slot;
    int delay;
    ///\todo change this to dynamic cast from boost
    std::istringstream iss ( commands[1].c_str() );
    iss >> slot;
    if ( commands.size() != 3 && commands.size() != 2 )
    {
        return sendMessage ( 406 );
    }
    if ( ! control->isValidSlot ( machine,slot ) )
    {
        return sendMessage ( 409 );
    }
    if ( control->getCost ( machine , slot ) > control->getCredits ( username ) )
    {
        return sendMessage ( 203 );
    }
    if ( commands.size() == 3 )
    {
        //this is to check if this all numbers
        if ( ! boost::regex_match ( commands[2].c_str(), numbers ) )
        {
            return sendMessage ( 403 );
        }
        else
        {
            ///\todo change this to dynamic cast from boost
            std::istringstream dss ( commands[2].c_str() );
            dss >> delay;
            int result = control->drop ( machine, username, slot );
            if ( result < 0 )
            {
                return sendMessage ( -result );
            }
            std::stringstream ss;
            ss <<"OK Credits remaining: "<<control->getCredits ( username ) << "\n";
            std::string response = ss.str();
            sendMessage ( response );
            return 0;
        }
    }
    //only time this is hit is when commands.size == 2
    else
    {
        int result = control->drop ( machine, username, slot );
        if ( result < 0 )
        {
            return sendMessage ( -result );
        }
        std::stringstream ss;
        ss <<"OK Credits remaining: "<<control->getCredits ( username ) << "\n";
        std::string response = ss.str();
        sendMessage ( response );
        return 0;
    }
}
/*!\brief The balance.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::getbalance ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "getbalance start"	<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( ! authenticated )
    {
        return sendMessage ( 204 );
    }
    else if ( commands.size() == 1 )
    {
        std::stringstream ss;
        ss <<"OK Credits : "<<control->getCredits ( username ) << "\n";
        std::string response = ss.str();
        sendMessage ( response );
        return 0;
    }
    else if ( commands.size() == 2 )
    {
        //Check if we are admin
        if ( !admin )
        {
            return sendMessage ( 200 );
        }
        if ( !control->isValidUser ( commands[1] ) )
        {
            return sendMessage ( 410 );
        }
        std::stringstream ss;
        ss <<"OK Credits : "<<control->getCredits ( commands[1] ) << "\n";
        sendMessage ( ss.str() );
        return 0;
    }
    else
    {
        return sendMessage ( 406 );
    }

}
/*!\brief The machine currently logged in to.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::location ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "location start" << std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( commands.size() != 1 )
    {
        return sendMessage ( 406 );
    }
    else
    {
        ///\todo add lookup for machine name here
        std::string response = "OK  <MACHINE NAME> .\n";
        sendMessage ( response );
        return 0;
    }
}
/*!\brief Pass, should be called after user.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::pass ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "pass start" << std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( username == "" )
    {
        return sendMessage ( 201 );
    }
    else if ( commands.size() != 2 )
    {
        return sendMessage ( 406 );
    }
    else
    {
        if ( control->authUser ( username, commands[1] ) )
        {
            //Since the user authenticated, check to see if administrator
            admin = control->isAdmin ( username );
            password = commands[1];
            authenticated = true;
            commands.clear();
            commands.push_back ( "GETBALANCE" );
            getbalance ( commands );
            return 0;
        }
        else
        {
            authenticated = false;
            return sendMessage ( 202 );
        }
    }
}
/*!\brief Disconnects the user from the server.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::quit ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "quit start" << std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    sendMessage ( "OK Disconnecting.\n" );
    close ( acceptedSocket );
    return -1;
}
/*!\brief Drops a random drink from a machine.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::rand ( std::vector<std::string> commands )
{
    boost::regex numbers ( "[[:digit:]]+" );//used to verify that input is all numbers
#ifdef DEBUG
    std::cout << "rand start" << std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( !authenticated )
    {
        return sendMessage ( 204 );
    }
    else if ( commands.size() == 1 )
    {
#ifdef DEBUG
        std::cout << "commands size == 1" << std::endl;
#endif
        //grab random slot from slots available then check if it's ok
        //drop with no time
        std::vector<int> availSlots = control->getValidSlots ( machine );
        int slot = ::rand() % availSlots.size();
        commands.clear();
        commands.push_back ( "drop" );
#ifdef DEBUG
        std::cout << "dropping from slot " << availSlots.at ( slot ) << std::endl;
#endif
        std::stringstream out;
        out << availSlots.at ( slot );
        commands.push_back ( out.str() );//used +"" so it converts to string
        return drop ( commands );
    }
    else if ( commands.size() == 2 )
    {
#ifdef DEBUG
        std::cout << "commands size == 2" << std::endl;
#endif
        if (	! boost::regex_match ( commands[1].c_str(), numbers ) )
        {
            return sendMessage ( 406 );
        }
        else
        {
            std::string delay = commands[1];
            //grab random slot from slots available then check if it's ok
            //drop with delay
            std::vector<int> availSlots = control->getValidSlots ( machine );
            int slot = ::rand() % availSlots.size();
            std::stringstream out;
            out << availSlots.at ( slot );
            commands.clear();
            commands.push_back ( "drop" );
            commands.push_back ( out.str() );//used +"" so it converts to string
            commands.push_back ( delay );
            return drop ( commands );
        }
    }
    else
    {
        return sendMessage ( 406 );
    }
}
/*!\brief Gets the stats for a slot or the entire machine.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::stat ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "stat start"<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    boost::regex numbers ( "[[:digit:]]+" );//used to verify that input is all numbers
    if ( commands.size() == 1 )
    {
        std::vector<std::string> result = control->getStats ( machine );
        for ( unsigned int i = 0; i < result.size(); ++i )
        {
            sendMessage ( result[i] );
        }
        return 0;
    }
    else if ( ( commands.size() == 2 ) &&
              ( boost::regex_match ( commands[1].c_str(), numbers ) ) )
    {
        int slot;
        std::istringstream dss ( commands[1].c_str() );
        dss >> slot;
        if ( ! control->isValidSlot ( machine, slot ) )
        {
            return sendMessage ( 409 );
        }
        std::vector<std::string> result = control->getStats ( machine, slot );
        for ( unsigned int i = 0; i < result.size(); ++i )
        {
            sendMessage ( result[i] );
        }
        return 0;
    }
    else
    {
        return sendMessage ( 406 );
    }
}
/*!\brief Gets the temperature of the current machine.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::temp ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "temp start" << std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( commands.size() == 1 )
    {
        int temp = control->getTemp ( machine );
        if ( temp != -2000 )
        {
            sendMessage ( "OK " + temp );
            return 0;
        }
        else
        {
            return sendMessage ( 351 );
        }
    }
    else
    {
        return sendMessage ( 406 );
    }
}
/*!\brief Sets the username to use.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::user ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "user start"<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( commands.size() == 2 )
    {
        authenticated = false;
        password = "";
        admin = false;
        username = commands[1];
        sendMessage ( "OK Password required.\n" );
        return 0;
    }
    else
    {
        return sendMessage ( 406 );
    }
}
/*!\brief Gives the username the user is currently identified as.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::whoami ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "whoami start"	<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( username == "" )
    {
        return sendMessage ( 201 );
    }
    else if ( commands.size() == 1 )
    {
        sendMessage ( "OK " + username + ".\n" );
        return 0;
    }
    else
    {
        return sendMessage ( 406 );
    }
}
/*!\brief Gets the version of the SUNDAY server.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::version ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "version start"<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( commands.size() != 1 )
    {
        return sendMessage ( 406 );
    }
    else
    {
        char * str = new char[20];
        sprintf ( str, "%.4g", control->version );
        sendMessage ( str );
        delete ( str );
        return 0;
    }
}
/*!\brief Adds credits to a user.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::addcredits ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "addcredits start"	<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    //verify that it is either a positive or negative number
    boost::regex numbers ( "-{0,1}[[:digit:]]+" );
    if ( !authenticated )
    {
        return sendMessage ( 204 );
    }
    else if ( !admin )
    {
        return sendMessage ( 200 );
    }
    else if ( commands.size() != 3 )
    {
        return sendMessage ( 406 );
    }
    //check to make sure the amount of credits is valid
    else if ( ( boost::regex_match ( commands[2].c_str(), numbers ) ) )
    {
        //Check to make sure the username is valid
        if ( !control->isValidUser ( commands[1] ) )
        {
            //User is not valid
            return sendMessage ( 410 );
        }
        //Everything is valid, so edit the user's credits
        std::stringstream ss ( commands[2] );
        int num;
        ss >> num;
        control->editCredits ( commands[1], num );
        sendMessage ( "OK Added credits.\n" );
        return 0;
    }
    else
    {
        return sendMessage ( 402 );
    }
}
/*!\brief Adds a new user.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::adduser ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "adduser start"<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( !authenticated )
    {
        return sendMessage ( 204 );
    }
    else if ( !admin )
    {
        return sendMessage ( 200 );
    }
    else if ( control->isValidUser ( commands[1] ) )
    {
        //User already exists
        return sendMessage ( 412 );
    }
    else if ( commands.size() ==2 || commands.size() == 3 )
    {
        //Doesn't matter what the pw is, we're throwing it away
        if ( control->addUser ( commands[1] ) )
        {
            sendMessage ( "OK User created.\n" );
            return 0;
        }
        else
        {
            return sendMessage ( 352 );
        }
    }
    else
    {
        return sendMessage ( 406 );
    }
}
//EDITSLOT <slotnum> <name> <cost> <quantity> <num_dropped> <enabled>
/*!\brief Edits a slot.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::editslot ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "editslot start" << std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( !authenticated )
    {
        return sendMessage ( 204 );
    }
    else if ( !admin )
    {
        return sendMessage ( 200 );
    }
    else if ( commands.size() != 7 )
    {
        return sendMessage ( 406 );
    }
    else
    {
        //0			1			2	 3			4			5			6
        //editslot <slotnum> <name> <cost> <quantity> <num_dropped> <enabled>
        boost::regex numbers ( "[[:digit:]]+" );//used to verify that input is all numbers
        if ( ! boost::regex_match ( commands[1].c_str(), numbers )
             ||
             ( ! control->isValidSlot ( machine,atoi ( commands[1].c_str() ) ) ) )
        {
            return sendMessage ( 409 );
        }
        //If the name of the item isn't wrapped in "
        boost::regex quotation ( "\".*\"" );
        if ( ! boost::regex_match ( commands[2].c_str(), quotation ) )
        {
            return sendMessage ( 406 );
        }
        if ( ! boost::regex_match ( commands[3].c_str(), numbers ) )
        {
            return sendMessage ( 401 );
        }
        if ( ! boost::regex_match ( commands[4].c_str(), numbers ) )
        {
            return sendMessage ( 408 );
        }
        if ( ! boost::regex_match ( commands[5].c_str(), numbers ) )
        {
            return sendMessage ( 405 );
        }

        boost::regex boolReg ( "true|false" , boost::regex::perl|boost::regex::icase );
        if ( ! boost::regex_match ( commands[6].c_str(), boolReg ) )
        {
            return sendMessage ( 404 );
        }
        boost::regex trueReg ( "true" , boost::regex::perl|boost::regex::icase );
        //Everything is correct, so actually edit the slot
        control->editSlot ( machine,
                            atoi ( commands[1].c_str() ),
                            commands[2],
                            atoi ( commands[3].c_str() ),
                            atoi ( commands[4].c_str() ),
                            atoi ( commands[5].c_str() ),
                            boost::regex_match ( commands[6].c_str(), trueReg ) );
        sendMessage ( "OK Changes saved.\n" );
        return 0;
    }
}
//EDITUSER <username> <credits> [admin]
/*!\brief Edits a user.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::edituser ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "edituser start"<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( !authenticated )
    {
        return sendMessage ( 204 );
    }
    else if ( !admin )
    {
        return sendMessage ( 200 );
    }
    else if ( ! control->isValidUser ( commands[1] ) )
    {
        return sendMessage ( 410 );
    }
    else if ( commands.size() == 4 )
    {
        boost::regex boolReg ( "true|false" , boost::regex::perl|boost::regex::icase );
        if ( ! boost::regex_match ( commands[3].c_str(), boolReg ) )
        {
            return sendMessage ( 400 );
        }
        boost::regex numbers ( "-{0,1}[[:digit:]]+" ); //used to verify that input is all numbers
        if ( ( ! boost::regex_match ( commands[2].c_str(), numbers ) ) )
        {
            return sendMessage ( 402 );
        }
        boost::regex trueReg ( "true" , boost::regex::perl|boost::regex::icase );
        control->editUser ( commands[1], atoi ( commands[2].c_str() ),
                            boost::regex_match ( commands[3].c_str(), trueReg ) );
        return sendMessage ( 0 );
    }
    else if ( commands.size() == 3 )
    {
        boost::regex numbers ( "-{0,1}[[:digit:]]+" );//used to verify that input is all numbers
        if ( ! boost::regex_match ( commands[2].c_str(), numbers ) )
        {
            return sendMessage ( 402 );
        }
        control->editUser ( commands[1], atoi ( commands[2].c_str() ) );
        return sendMessage ( 0 );
    }
    else
    {
        return sendMessage ( 406 );
    }
}
//ISVALIDUSER <user>
/*!\brief Writes if the user is valid or not.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::isvaliduser ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "isvaliduser start"<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( !authenticated )
    {
        return sendMessage ( 204 );
    }
    else if ( !admin )
    {
        return sendMessage ( 200 );
    }
    else if ( commands.size() == 2 )
    {
        std::string response;
        if ( control->isValidUser ( commands[1] ) )
        {
            response = "OK true " + commands[1] + " is known.\n";
        }
        else
        {
            response = "OK false " + commands[1] + " is not known.\n";
        }
        sendMessage ( response );
        return 0;
    }
    else
    {
        return sendMessage ( 406 );
    }
}
//LOG [message]
/*!\brief Adds a message to the log.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::log ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "log start"<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( !authenticated )
    {
        return sendMessage ( 204 );
    }
    else if ( !admin )
    {
        return sendMessage ( 200 );
    }
    else
    {
        control->addToLog ( username, commands );
        sendMessage ( "OK Message added to log file.\n" );
        return 0;
    }
}
//QUERYADMIN <user>
/*!\brief Writes if the user is an admin or not.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::queryadmin ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "queryadmin start"	<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( commands.size() != 2 )
    {
        return sendMessage ( 406 );
    }
    else if ( !authenticated )
    {
        return sendMessage ( 204 );
    }
    else if ( !admin )
    {
        return sendMessage ( 200 );
    }
    else if ( !control->isValidUser ( commands[1] ) )
    {
        return sendMessage ( 410 );
    }
    else
    {
        std::string response;
        if ( control->isAdmin ( commands[1] ) )
        {
            response = "OK true " + commands[1]  + " is an administrator.\n";
        }
        else
        {
            response = "OK false " +commands[1] + " is not an administrator.\n";
        }
        sendMessage ( response );
        return 0;
    }
}
//RMUSER <user>
/*!\brief Remove's a user's Drink account.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::rmuser ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "rmuser start"	<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( !authenticated )
    {
        return sendMessage ( 204 );
    }
    else if ( !admin )
    {
        return sendMessage ( 200 );
    }
    else if ( commands.size() != 2 )
    {
        return sendMessage ( 406 );
    }
    else if ( !control->isValidUser ( commands[1] ) )
    {
        return sendMessage ( 410 );
    }
    else
    {
        std::string response;
        int returnVal;
        if ( control->removeUser ( commands[1] ) )
        {
            response = "OK User removed.\n";
            returnVal = 0;
        }
        else
        {
            response = control->err->errorMap[353];
            returnVal = 353;
        }
        sendMessage ( response );
        return returnVal;
    }
}
//SETADMIN <user name> <status>
/*!\brief Adds or removes a user's admin status.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::setadmin ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "setadmin start" << std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( !authenticated )
    {
        return sendMessage ( 204 );
    }
    else if ( !admin )
    {
        return sendMessage ( 200 );
    }
    else if ( commands.size() != 3 )
    {
        return sendMessage ( 406 );
    }
    else if ( !control->isValidUser ( commands[1] ) )
    {
        return sendMessage ( 410 );
    }
    else if ( commands[2] != "false" || commands[2] != "true" )
    {
        return sendMessage ( 400 );
    }
    else
    {
        std::string response;
        int returnVal;
        if ( control->setAdmin ( commands[1], commands[2] ) )
        {
            response = "OK Admin flag set.\n";
            returnVal = 0;
        }
        else
        {
            response = control->err->errorMap[354];
            returnVal = 354;
        }
        sendMessage ( response );
        return returnVal;
    }
}
//SHUTDOWN [-r]
/*!\brief Shutdowns and optionally restarts the server.
 * \param commands a vector of strings containing the tokenized commands
 * \return An integer specifying the result
 */
int Command::shutdown ( std::vector<std::string> commands )
{
#ifdef DEBUG
    std::cout << "shutdown start"<< std::endl;
    std::cout << "user: " << userNum << std::endl;
#endif
    if ( !authenticated )
    {
        return sendMessage ( 204 );
    }
    else if ( !admin )
    {
        return sendMessage ( 200 );
    }
    else if ( commands.size() == 2 )
    {
        if ( commands[2] != "-r" )
        {
            return sendMessage ( 411 );
        }
        sendMessage ( "OK Rebooting.\n" );
        control->shutdown ( true );
        return 0;
    }
    else if ( commands.size() == 1 )
    {
        sendMessage ( "OK Shutting down server.\n" );
        control->shutdown ( false );
        return 0;
    }
    else
    {
        return sendMessage ( 451 );
    }
}
/*!\brief Parses what the client sent and passes it off to the appropriate
 * function.
 * \param command a char array containing the entire line the user sent
 * \param length the length of the string
 * \return An integer specifying the result
 */
int Command::interpretCommand ( char command[], int length )
{
    //Tokenize the input so we can actually call the proper commands
    std::vector<std::string> commands = tokenize ( command, length );
    std::string firstCommand = commands.at ( 0 );
    //convert the command to all lowercase
    for ( int unsigned i = 0; i < firstCommand.length(); ++i )
    {
        if ( firstCommand[i] < 91 && firstCommand[i] > 64 )
            firstCommand[i] = firstCommand[i]+32;
    }
#ifdef DEBUG
    std::cout << "First Command:" << firstCommand << std::endl;
#endif
    //i'm sure there is a prettier way to do this, but c++ doesn't allow
    //switch statements off of strings, so we get the following huge-ass
    //if statements
    //could possibly optimize this by splitting up between admin
    //and non-admin commands and/or length of string, etc
    if ( firstCommand == "acctmgrchk" )
    {
        return acctmgrchk ( commands );
    }
    else if ( firstCommand == "code" )
    {
        return code ( commands );
    }
    else if ( firstCommand == "drop" )
    {
        return drop ( commands );
    }
    else if ( firstCommand == "location" )
    {
        return location ( commands );
    }
    else if ( firstCommand == "pass" )
    {
        return pass ( commands );
    }
    else if ( firstCommand == "quit" )
    {
        return quit ( commands );
    }
    else if ( firstCommand == "rand" )
    {
        return rand ( commands );
    }
    else if ( firstCommand == "stat" )
    {
        return stat ( commands );
    }
    else if ( firstCommand == "temp" )
    {
        return temp ( commands );
    }
    else if ( firstCommand == "user" )
    {
        return user ( commands );
    }
    else if ( firstCommand == "whoami" )
    {
        return whoami ( commands );
    }
    else if ( firstCommand == "version" )
    {
        return version ( commands );
    }
    else if ( firstCommand == "addcredits" )
    {
        return addcredits ( commands );
    }
    else if ( firstCommand == "adduser" )
    {
        return adduser ( commands );
    }
    else if ( firstCommand == "chpass" )
    {
        return chpass ( commands );
    }
    else if ( firstCommand == "editslot" )
    {
        return editslot ( commands );
    }
    else if ( firstCommand == "edituser" )
    {
        return edituser ( commands );
    }
    else if ( firstCommand == "getbalance" )
    {
        return getbalance ( commands );
    }
    else if ( firstCommand == "isvaliduser" )
    {
        return isvaliduser ( commands );
    }
    else if ( firstCommand == "log" )
    {
        return log ( commands );
    }
    else if ( firstCommand == "queryadmin" )
    {
        return queryadmin ( commands );
    }
    else if ( firstCommand == "rmuser" )
    {
        return rmuser ( commands );
    }
    else if ( firstCommand == "setadmin" )
    {
        return setadmin ( commands );
    }
    else if ( firstCommand == "shutdown" )
    {
        return shutdown ( commands );
    }
    else
    {
        return ( unknowncommand () );
    }
}
/*!\brief Pulls apart the char array by spaces and puts it in a vector.
 * \param arg a character array containing the user's input
 * \param length the length of the user's input
 * \return A vector of strings which is the tokenized input
 */
std::vector<std::string> Command::tokenize ( char arg[], int length )
{
    int whitespaceLoc = 0;//where the next whitespace is
    int oldWhitespaceLoc = 0;
    int stringLength;//the length of the entire string
    bool firstRun = true;//if this is the first time the loop is goin thru
    std::vector<std::string> result = std::vector<std::string>();
    std::string tempStr = " ";

    //Use find to get each place a space is, and then get the substring
    //between each space in order to get each token
    //hopefully don't need to worry about extra spaces
    std::string stringArg = std::string ( arg );
    stringLength = stringArg.length();
    //while there are still whitespaces to break by, keep tokenizing
    //this code is really messy but it works, don't look too hard at it
    //too many magic numbers and gotchas
    whitespaceLoc = stringArg.find ( " ", whitespaceLoc );
    while ( whitespaceLoc != -1 && whitespaceLoc < length )
    {
        if ( firstRun )
        {
            tempStr =
                stringArg.substr ( oldWhitespaceLoc, whitespaceLoc-oldWhitespaceLoc );
            firstRun = false;
        }
        else
        {
            tempStr =
                //+1 is to avoid adding the actual space
                stringArg.substr ( oldWhitespaceLoc + 1,
                                   whitespaceLoc-oldWhitespaceLoc - 1 );
        }
        result.push_back ( tempStr );
        oldWhitespaceLoc = whitespaceLoc++;
        whitespaceLoc = stringArg.find ( " ", whitespaceLoc );
    }
    if ( !firstRun )
    {
        //The -3 is to pull off the extra whitespace and shit
        tempStr =
            stringArg.substr ( oldWhitespaceLoc + 1, length-oldWhitespaceLoc-3 );
    }
    else
    {
        tempStr =
            stringArg.substr ( oldWhitespaceLoc, length-oldWhitespaceLoc-2 );
    }
#ifdef DEBUG
    std::cout << "final value:" << tempStr << std::endl;
#endif

    result.push_back ( tempStr );

#ifdef DEBUG
    for ( unsigned int i = 0; i < result.size(); ++i )
    {
        std::cout<<"Vector["<< i << "] : [" <<result.at ( i ) << "]\n" << std::endl;
    }
#endif
    return result;
}

/*!\brief Sends a message.
 * \param message the message to send
 */
void Command::sendMessage ( std::string message )
{
    write ( acceptedSocket, message.c_str(), strlen ( message.c_str() ) );
}

/*!\brief Sends a message.
 * \param errorNum the error number to write to the user
 * \return the inverse of the errorNum
 */
int Command::sendMessage ( int errorNum )
{
    write ( acceptedSocket, control->err->errorMap[errorNum].c_str(), strlen ( control->err->errorMap[errorNum].c_str() ) );
    return -errorNum;
}
