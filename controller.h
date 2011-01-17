#ifndef CONTROLLER_HEADER
#define CONTROLLER_HEADER
#include <map>
#include <string>
#include <vector>
#ifdef DEBUG
#include <iostream>
#endif
///Used to keep track of all the error messages
class ErrorMessages
{
public:
    ///Actual map for the errors
    std::map<int,std::string> errorMap;
    ///Constructor that instantiates and assigns the error map
    ErrorMessages()
    {
        errorMap = std::map<int,std::string>();
#ifdef DEBUG
        std::cout << "ErrorMessages constructor" << std::endl;
#endif
        //General drop errors
        errorMap[100] = "ERR 100 Slot empty.\n";
        errorMap[101] = "ERR 101 Drop failed, contact an admin.\n";
        errorMap[102] = "ERR 102 Slot disabled.\n";
        errorMap[103] = "ERR 103 Unknown Failure.\n";
        errorMap[104] = "ERR 104 No slots available.\n";

        //electronic drop errors
        errorMap[150] = "ERR 150 Unable to initialize hardware for drop.\n";
        errorMap[151] = "ERR 151 Unable to communicate with hardware. Contact an admin.\n";

        //mechanical drop errors
        errorMap[175] = "ERR 175 Motor is jammed. Contact an admin immediately/\n";
        errorMap[176] = "ERR 176 Unable to start motor.\n";
        errorMap[177] = "ERR 177 Motor failure, can jam, or cutoff switch is off.\n";
        //authentication/permission errors
        errorMap[200] = "ERR 200 Access denied.\n";
        errorMap[201] = "ERR 201 USER command needs to be issued first.\n";
        errorMap[202] = "ERR 202 Invalid username or password.\n";
        errorMap[203] = "ERR 203 User is poor.\n";
        errorMap[204] = "ERR 204 You need to login.\n";
        errorMap[205] = "ERR 205 Maximum user count reached.\n";

        //subsystem failures
        errorMap[350] = "ERR 350 Account server subsystem is not ready.\n";
        errorMap[351] = "ERR 351 Unable to determine temperature.\n";
        errorMap[352] = "ERR 352 Unable to create user.\n";
        errorMap[353] = "ERR 353 Could not remove user.\n";
        errorMap[354] = "ERR 354 Unable to set admin flag.\n";

        //parameter errors
        errorMap[400] = "ERR 400 Invalid admin flag.\n";
        errorMap[401] = "ERR 401 Invalid cost.\n";
        errorMap[402] = "ERR 402 Invalid credits.\n";
        errorMap[403] = "ERR 403 Invalid delay.\n";
        errorMap[404] = "ERR 404 Invalid enable flag.\n";
        errorMap[405] = "ERR 405 Invalid num_dropped.\n";
        errorMap[406] = "ERR 406 Invalid parameters.\n";
        errorMap[407] = "ERR 407 Invalid password.\n";
        errorMap[408] = "ERR 408 Invalid quantity.\n";
        errorMap[409] = "ERR 409 Invalid slot.\n";
        errorMap[410] = "ERR 410 Invalid user.\n";
        errorMap[411] = "ERR 411 Invalid reboot flag.\n";
        errorMap[412] = "ERR 412 User already registered.\n";

        //misc errors or failures
        errorMap[450] = "ERR 450 Timeout, disconnecting.\n";
        errorMap[451] = "ERR 451 Not implemented.\n";
        errorMap[452] = "ERR 452 Invalid command.\n";

    }
};
/*!\brief Talks to mysql, ldap, and the tinis.
 * This class contains all the mysql, ldap, talking to tini's
 * and other common crap. There is only ever one of this class
 * instantiated.
 * This class assumes that all username, admin, authentication
 *checks are already made before the function is called.
 * For example, add user should have isAdmin and isValidUser checked
 * from the command class rather than here.
 */
class Controller
{
    ///\todo Change this to private with command as a friend
public:
    ///The current version of the software.
    static const float version = .2;
    static Controller* Instance();
    static ErrorMessages* err;
    ~Controller();
    bool authUser ( std::string user, std::string pass );
    bool addUser ( std::string username );
    bool isAvailable();
    bool editSlot ( std::string machine,int slotnum, std::string name, int cost, int quantity, int numDropped, bool enabled );
    bool isValidSlot ( std::string machine, int slot );
    bool isValidUser ( std::string username );
    void addToLog ( std::string username,
                    std::vector<std::string>message );
    bool isAdmin ( std::string user );
    bool removeUser ( std::string user );
    bool setAdmin ( std::string user, std::string admin );
    int drop ( std::string machine, std::string user, int slot );
    void shutdown ( bool restart );
    int getCredits ( std::string user );
    bool editCredits ( std::string user, int credits );
    bool editUser ( std::string user, int credits, bool admin );
    bool editUser ( std::string user, int credits );
    int getCost ( std::string machine, int slot );
    std::vector<int> getValidSlots ( std::string machine );
    std::vector<std::string> getStats ( std::string machine );
    std::vector<std::string> getStats ( std::string machine, int slotNum );
    int getTemp ( std::string machine );
protected:
    Controller();
private:
    static Controller* _instance;
};
#endif
