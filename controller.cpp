#include "controller.h"
#include <stdlib.h>
#ifdef DEBUG
#include <iostream>
#endif
///Reference to the controller instance.
Controller* Controller::_instance = 0;
///Reference to the error messages.
ErrorMessages* Controller::err = 0;

/*!\brief Returns the instance of controller.
 * \return Reference to the only instance of the controller class.
 * If the controller has already been constructed, this returns a reference to
 * it, otherwise it creates the controller and then returns an instance to it.
 */
Controller* Controller::Instance()
{
    if ( _instance == 0 )
    {
        _instance = new Controller;
        err = new ErrorMessages;
    }
    return _instance;
}
/*!\brief Default constructor for controller
 *
 */
Controller::Controller()
{
#ifdef DEBUG
    std::cout << "Controller constructor" << std::endl;
#endif
    mysqlUsername = "########";
    mysqlPassword = "########";
    mysqlServerAddress = "127.0.0.1";
    mysqlDbName = "########";
    mysqlPortNumber = 3306;
    //Instantiate and connect to the server
    conn = mysqlpp::Connection ( mysqlDbName.c_str(), mysqlServerAddress.c_str(),
                                 mysqlUsername.c_str(), mysqlPassword.c_str(),
                                 mysqlPortNumber );
    if ( ! conn.connected() )
    {
        std::cerr << "Error Connecting to Mysql Database" << std::endl;
    }
    else
    {
#ifdef DEBUG
        std::cout << "Connected to Mysql Database" << std::endl;
#endif
    }

    ///\todo double check to make sure the database isn't going to kick off an open connection if it idles too long
    ///\todo add code to handle if the program loses a connection with the database
}

/*!\brief Frees up any memory allocated during construction.
 *
 */
Controller::~Controller()
{
    conn.disconnect();
    delete ( Instance() );
}

/*!\brief Returns whether or not this user/pass is valid.
 * \param user the username to check
 * \param pass the password to check
 * \return Whether or not the username and password is valid
 *
 * Checks the username/password combination against ldap.
 */
bool Controller::authUser ( std::string user, std::string pass )
{
    boost::mutex::scoped_lock lock ( ldapMutex );
    ///\todo Fix this
    return ( ( user == "poor" && pass == "poor" ) || ( user == "bab" && pass == "bab" ) || ( user == "admin" && pass == "admin" ) );
}
/*!\brief Returns whether or not the server is available.
 * \return Whether or not the server is available.
 */
bool Controller::isAvailable()
{
    ///\todo Fix this
    return true;
}
/*!\brief Returns whether or not this is a valid slot.
 * \param machine the machine to check the slot on
 * \param slot the slot number to check
 * \return Whether or not the slot is valid for the machine
 */
bool Controller::isValidSlot ( int machine, int slot )
{
    ///\todo Fix this
    //select count(snum) from slotProperty where mid = <machine> and snum = <slot> and disabled = 0
    mysqlpp::Query::Query query = mysqlpp::Query::Query(&conn, false, 
      ("select count(snum) > 0 from slotProperty where mid=" 
      + boost::lexical_cast<std::string>(machine) + "and snum=" 
      + boost::lexical_cast<std::string>(slot) + " and disabled=0").c_str());
    #ifdef DEBUG
      std::cout << query.exec() << std::endl;
    #endif
    
    //return false;
    return ( query.exec() );
}

/*!\brief Returns whether or not this user is valid.
 * \param username the username to check
 * \return Whether or not the username exists
 *
 * Checks the username against ldap.
 */
bool Controller::isValidUser ( std::string username )
{
    boost::mutex::scoped_lock lock ( ldapMutex );
    ///\todo Fix this
    return ( username == "bab" );
    //return false;
}
/*!\brief Adds the specified (if any) message to the message log.
 * \param username the user that is adding to the log
 * \param message the message(if any) that is to be added to the log
 *
 * Adds the specified message to the message log, if there is no message, it
 * just adds the username to the log.
 */
void Controller::addToLog ( std::string username,std::vector<std::string>message )
{
    boost::mutex::scoped_lock lock ( mysqlMutex );
    ///\todo Fix this
    //start at vector[1]
}
/*!\brief Returns whether or not the user is an admin.
 * \param user the user to check
 * \return Whether or not the user is an admin
 */
bool Controller::isAdmin ( std::string user )
{
    boost::mutex::scoped_lock lock ( ldapMutex );
    ///\todo Fix this
    return ( user == "admin" );
//	return false;
}
/*!\brief Removes a user's drink account.
 * \param user the user account to remove
 * \return Whether or not the removal was succesful
 */
bool Controller::removeUser ( std::string user )
{
    boost::mutex::scoped_lock lock ( ldapMutex );
    ///\todo Fix this
    return false;
}
/*!\brief Either add or removes a user's admin priveledges.
 * \param user the user to alter
 * \param admin the string specifying whether adding or removing privs
 * \return Whether or not the alteration was succesful
 */
bool Controller::setAdmin ( std::string user, std::string admin )
{
    boost::mutex::scoped_lock lock ( ldapMutex );
    ///\todo Fix this
//	bool setAdmin = admin == "true";
    return false;
}
/*!\brief Shuts down the machine running this server.
 * \param restart Whether or not to restart the machine after shutting down.
 *
 * This doesn't guarantee that the service starts back up with the machine,
 * need to make alternate arrangements such as adding a startup script or such.
 */
void Controller::shutdown ( bool restart )
{
    if ( restart )
    {
        system ( "shutdown -r now" );
    }
    else
    {
        system ( "shutdown now" );
    }
}
/*!\brief Drops a drink.
 * \param machine the machine to drop the drink from
 * \param user the user that is dropping the drink
 * \param slot the slot number to drop from
 * \return An integer specifying the result(0 for success, -n for failure)
 *
 * Drops the drink, this function assumes that the user has enough credits.
 * ONCE AGAIN, DO NOT CALL THIS UNLESS THE USER HAS ENOUGH CREDITS OR YOU ARE RETARDED.
 */
int Controller::drop ( int machine, std::string user, int slot )
{
    ///\todo change this to something that allows multiple locks
    boost::mutex::scoped_lock lock ( ldapMutex );
    // boost::mutex::scoped_lock lock ( tiniMutex );
    ///\todo actually call the drop
    return 0;
}
/*!\brief Returns how many credits the user has.
 * \param user the user to check
 * \return How many credits the user has
 */
int Controller::getCredits ( std::string user )
{
    boost::mutex::scoped_lock lock ( ldapMutex );
    ///\todo Implement
    if ( user != "poor" ) return 5;
    return 0;
}
/*!\brief Returns all valid slots for the machine.
 * \param machine the machine to return the valid slots on
 * \return A vector containing all valid slots
 */
std::vector<int> Controller::getValidSlots ( int machine )
{
    boost::mutex::scoped_lock lock ( tiniMutex );
    std::vector<int> returnVal;
    ///\todo Implement
    returnVal.push_back ( 0 );
    return returnVal;
}
/*!\brief Returns all the stats for the specified machine.
 * \param machine the machine to return the stats on
 * \return All the stats for the machine.
 */
std::vector<std::string> Controller::getStats ( int machine )
{
    boost::mutex::scoped_lock lock ( tiniMutex );
    std::vector<std::string> result;
    result.push_back ( "0 \"Coke\" 50 13 200 true" );
    result.push_back ( "OK 1 Slots retrieved" );
    ///\todo implement
    //if the machine is invalid, return nothing
    //else add slots
    return result;
}
/*!\brief Returns the stats for a slot on a machine.
 * \param machine the machine the slot is in
 * \param slotNum the slot number to get the stat for
 * \return The stat for the specified machine and slot number
 */
std::vector<std::string> Controller::getStats ( int machine, int slotNum )
{
    boost::mutex::scoped_lock lock ( tiniMutex );
    std::vector<std::string> result;
    result.push_back ( "0 \"Coke\" 50 13 200 true" );
    result.push_back ( "OK 1 Slots retrieved" );
    ///\todo implement
    //if the machine is invalid, return nothing
    //else add slots
    return result;
}
/*!\brief Returns the cost of the drink in the specified slot.
 * \param machine the machine the slot is in
 * \param slotNum the slot number to get the stat for
 * \return The stat for the specified machine and slot number
 */
int Controller::getCost ( int machine, int slotNum )
{
    boost::mutex::scoped_lock lock ( tiniMutex );
    ///\todo implement this
    return 1;
}
/*!\brief Returns the temperature of the machine.
 * \param machine the machine to check the temperature on
 * \return The temperature for the machine, -2000 if the machine doesn't support
 * temperature.
 */
int Controller::getTemp ( int machine )
{
    boost::mutex::scoped_lock lock ( tiniMutex );
    ///\todo Implement, -2000 means that there was a problem getting the temp
    ///\todo Change -2000 to a static const
    if ( machine != 0 )
    {
        return -2000;
    }
    else
    {
        return 5;
    }
}
/*!\brief Adds or subtracts credits to a user.
 * \param user the user to edit credits for
 * \param credits the amount of credits to add or remove
 * \return whether or not the edit was succesful
 */
bool Controller::editCredits ( std::string user, int credits )
{
    boost::mutex::scoped_lock lock ( ldapMutex );
    ///\todo Implement adding credits to a user
    return false;
}
/*!\brief Adds a new user to the DRINK system
 * \param username the user to add
 * \return whether or not adding the new user was succesful
 */
bool Controller::addUser ( std::string username )
{
    boost::mutex::scoped_lock lock ( ldapMutex );
    ///\todo implement this
    return true;
}
/*!\brief Edits a slot
 * \param machine the machine the slot is on
 * \param slotnum the slot number of the product
 * \param name	the name of the product (encased in quotation marks)
 * \param cost the cost of the product
 * \param quantity the amount available
 * \param numDropped the amount already dropped
 * \param enabled whether or not this slot is enabled
 * \return whether or not editing the slot was succesful
 */
bool Controller::editSlot ( int machine,int slotnum, std::string name, int cost, int quantity, int numDropped, bool enabled )
{
    boost::mutex::scoped_lock lock ( tiniMutex );
    ///\todo implement this
    return true;
}
/*!\brief Edits an existing user.
 * \param user the user to edit
 * \param credits the amount of credits to add or remove
 * \return whether or not the edit was succesful
 */
bool Controller::editUser ( std::string user, int credits )
{
    boost::mutex::scoped_lock lock ( ldapMutex );
    ///\todo implement this
    return false;
}
/*!\brief Edits an existing user.
 * \param user the user to edit
 * \param credits the amount of credits to add or remove
 * \param admin either enables admin access or removes it
 * \return whether or not the edit was succesful
 */
bool Controller::editUser ( std::string user, int credits, bool admin )
{
    boost::mutex::scoped_lock lock ( ldapMutex );
    ///\todo implement this
    return false;
}
