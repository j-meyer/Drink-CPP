#include "unittest1.h"
#include "../sunday.h"
#include "../command.h"
#include "gtest/gtest.h"
#include <string>
#include <vector>
using namespace std;
namespace
{
class CommandTest : public ::testing::Test
{
protected:
    //typedef Command::Command command;
    // The fixture for testing class Foo.
    // You can remove any or all of the following functions if its body
    // is empty.
    CommandTest()
    {
        // You can do set-up work for each test here.
        //Command::Command command(0, "BD");
    }
    virtual ~CommandTest()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp()
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    //Objects declared here can be used by all tests in the test case for Foo.
};
class acctmgrchkTest : public ::testing::Test {};
class chpassTest : public ::testing::Test {};
class codeTest : public ::testing::Test {};
class dropTest : public ::testing::Test {};
class getBalanceTest : public ::testing::Test {};
class locationTest : public ::testing::Test {};
class passTest : public ::testing::Test {};
class quitTest : public ::testing::Test {};
class randTest : public ::testing::Test {};
class statTest : public ::testing::Test {};
class tempTest : public ::testing::Test {};
class userTest : public ::testing::Test {};
class versionTest : public ::testing::Test {};

class addCreditsTest : public ::testing::Test {};
class addUserTest : public ::testing::Test {};
class editSlotTest : public ::testing::Test {};
class editUserTest : public ::testing::Test {};
class isValidUserTest : public ::testing::Test {};
class logTest : public ::testing::Test {};
class queryAdminTest : public ::testing::Test {};
class rmUserTest : public ::testing::Test {};
class setAdminTest : public ::testing::Test {};
class shutdownTest : public ::testing::Test {};
std::string adminName = "admin";//valid admin username
std::string adminPassword = "admin";//valid admin password

std::string accountName = "bab";//a valid account name
std::string accountPw = "bab";//password for the above account

std::string invalidAccountName = "baadffadsdfsadfsb";//a valid account name

std::string poorUsername = "poor";//username to a user with no cash
std::string poorUserPw = "poor";

std::string newUserName = "tacobab";//a username that currently doesn't exist
std::string newUserPass = "tacobab";//a username that currently doesn't exist

std::string validSlotNum = "0";//a slot that is validSlotNum
std::string invalidSlotNum = "34343434";//an invalid slot num
//TODO: replace all instances of BD with machineName
std::string machineName = "BD";//name of the machine we're currently using
}

//#############
//Acctmgrchk
//#############
//Passes if it returns bad parameters when supplying too many
TEST ( acctmgrchkTest, WrongNumOfArgs )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "acctmgrchk" );
    arg.push_back ( accountName );
    command.acctmgrchk ( arg );
    EXPECT_EQ ( -406, command.acctmgrchk ( arg ) );
}
//Passes if the server actually passes
TEST ( acctmgrchkTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "acctmgrchk" );
    command.acctmgrchk ( arg );
    EXPECT_EQ ( 0, command.acctmgrchk ( arg ) );
}
//#############
//Chpass
//#############
//Passes if it isn't implemented
TEST ( chpassTest, NotImplemented )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "chpass" );
    arg.push_back ( accountName );
    command.acctmgrchk ( arg );
    EXPECT_EQ ( -451, command.chpass ( arg ) );
}
//#############
//Code
//#############
//Passes if it isn't implemented
TEST ( codeTest, NotImplemented )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "code" );
    arg.push_back ( "5" );
    arg.push_back ( "5 6 7 8 9" );
    command.acctmgrchk ( arg );
    EXPECT_EQ ( -451, command.code ( arg ) );
}
//#############
//Drop
//#############
TEST ( dropTest, NormalNoDelay )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "drop" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "0" );
    EXPECT_EQ ( 0, command.drop ( arg ) );
}
TEST ( dropTest, NormalDelay )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "drop" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "5" );
    EXPECT_EQ ( 0, command.drop ( arg ) );
}
//Too many args
TEST ( dropTest, WrongNumOfArgs )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "drop" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "0" );
    arg.push_back ( "0" );
    EXPECT_EQ ( -406, command.drop ( arg ) );
}
//Invalid Slot
TEST ( dropTest, InvalidSlot )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "drop" );
    arg.push_back ( invalidSlotNum );
    arg.push_back ( "55" );
    EXPECT_EQ ( -409, command.drop ( arg ) );
}
//Poor User
TEST ( dropTest, PoorUser )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( poorUsername );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( poorUserPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "drop" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "5" );
    EXPECT_EQ ( -203, command.drop ( arg ) );
}
//Need to login
TEST ( dropTest, NoLogin )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "drop" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "0" );
    EXPECT_EQ ( -204, command.drop ( arg ) );
}
//#############
//Drop - Delay
//#############
//TODO: maybe combine this with above
TEST ( dropDelayTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "drop" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "5" );
    EXPECT_EQ ( 0, command.drop ( arg ) );
}
//Invalid Delay
TEST ( dropDelayTest, InvalidDelay )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "drop" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "bab" );
    EXPECT_EQ ( -403, command.drop ( arg ) );
}
//#############
//Get Balance
//#############
//Normal User get balance
TEST ( getBalanceTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "getbalance" );
    EXPECT_EQ ( 0, command.getbalance ( arg ) );
}
//Get balance no login
TEST ( getBalanceTest, NoLogin )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "getbalance" );
    EXPECT_EQ ( -204, command.getbalance ( arg ) );
}
//Get balance too many args
TEST ( getBalanceTest, InvalidArgNum )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "getbalance" );
    arg.push_back ( "grg" );
    arg.push_back ( "grg" );
    EXPECT_EQ ( -406, command.getbalance ( arg ) );
}
//#############
//Location
//#############
//Normal get location
TEST ( locationTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "location" );
    EXPECT_EQ ( 0, command.location ( arg ) );
}
//Get location bad args
TEST ( locationTest, InvalidArgNum )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "location" );
    arg.push_back ( "location" );
    arg.push_back ( "location" );
    EXPECT_EQ ( -406, command.location ( arg ) );
}
//#############
//Pass
//#############
//Normal pass
TEST ( passTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
}
//Invalid password
TEST ( passTest, InvalidPassword )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw + "grg" );
    EXPECT_EQ ( -202, command.pass ( arg ) );
}
//No user command entered
TEST ( passTest, NoUser )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( -201, command.pass ( arg ) );
}
//Too many args
TEST ( passTest, InvalidNumArgs )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    arg.push_back ( "grg" );
    EXPECT_EQ ( -406, command.pass ( arg ) );
}
//#############
//Quit
//#############
//Normal quit
TEST ( quitTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "quit" );
    EXPECT_EQ ( -1, command.quit ( arg ) );
}
//#############
//Rand
//#############
//Normal rand
TEST ( randTest, NormalNoDelay )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "rand" );
    EXPECT_EQ ( 0, command.rand ( arg ) );
}
//Rand Normal delay
TEST ( randTest, NormalDelay )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "rand" );
    arg.push_back ( "5" );
    EXPECT_EQ ( 0, command.rand ( arg ) );
}
//Rand no login
TEST ( randTest, NoLogin )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "rand" );
    EXPECT_EQ ( -204, command.rand ( arg ) );
}
//Rand poor
TEST ( randTest, Poor )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( poorUsername );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( poorUserPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "rand" );
    arg.push_back ( "5" );
    EXPECT_EQ ( -203, command.rand ( arg ) );
}
//#############
//Stat
//##############
//Stat - no index
TEST ( statTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "stat" );
    EXPECT_EQ ( 0, command.stat ( arg ) );
}
//Stat - index
TEST ( statTest, NormalIndex )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "stat" );
    arg.push_back ( validSlotNum );
    EXPECT_EQ ( 0, command.stat ( arg ) );
}
//Stat - bad index
TEST ( statTest, BadIndex )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "stat" );
    arg.push_back ( invalidSlotNum );
    EXPECT_EQ ( -409, command.stat ( arg ) );
}
//Stat - invalid index
TEST ( statTest, InvalidIndex )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "stat" );
    arg.push_back ( "bab" );
    EXPECT_EQ ( -406, command.stat ( arg ) );
}
//Stat - too many params
TEST ( statTest, BadNumArgs )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "stat" );
    arg.push_back ( validSlotNum );
    arg.push_back ( validSlotNum );
    EXPECT_EQ ( -406, command.stat ( arg ) );
}
//#############
//Temp
//##############
//Temp Normal
TEST ( tempTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "temp" );
    EXPECT_EQ ( 0, command.temp ( arg ) );
}
//No temp for machine
TEST ( tempTest, TempLilDrink )
{
    Command::Command command ( 0, "LD", 0 );
    vector<string> arg;
    arg.push_back ( "temp" );
    EXPECT_EQ ( -351, command.temp ( arg ) );
}
//Too many args
TEST ( tempTest, BadNumArgs )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "temp" );
    arg.push_back ( "temp" );
    arg.push_back ( "temp" );
    arg.push_back ( "temp" );
    EXPECT_EQ ( -406, command.temp ( arg ) );
}
//#############
//User
//##############
//User Normal
TEST ( userTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
}
//User no username
TEST ( userTest, NoUser )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    EXPECT_EQ ( -406, command.user ( arg ) );
}
//User too many args
TEST ( userTest, BadNumArgs )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    arg.push_back ( accountName );
    EXPECT_EQ ( -406, command.user ( arg ) );
}
//#############
//Version
//##############
//Version Normal
TEST ( versionTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "version" );
    EXPECT_EQ ( 0, command.version ( arg ) );
}
//Version Bad args
TEST ( versionTest, BadNumArgs )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "version" );
    arg.push_back ( "bab" );
    EXPECT_EQ ( -406, command.version ( arg ) );
}
//############
//Add Credits
//###########
//Normal Add Credits
TEST ( addCreditsTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "addcredits" );
    arg.push_back ( accountName );
    arg.push_back ( "-5" );
    EXPECT_EQ ( 0, command.addcredits ( arg ) );
}
//Add Credits, No admin
TEST ( addCreditsTest, NoAdmin )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "addcredits" );
    arg.push_back ( accountName );
    arg.push_back ( "5" );
    EXPECT_EQ ( -200, command.addcredits ( arg ) );
}
//Add Credits, bad username
TEST ( addCreditsTest, InvalidUser )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "addcredits" );
    arg.push_back ( invalidAccountName );
    arg.push_back ( "5" );
    EXPECT_EQ ( -410, command.addcredits ( arg ) );
}
//Add Credits invalid credits
TEST ( addCreditsTest, InvalidCredits )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "addcredits" );
    arg.push_back ( accountName );
    arg.push_back ( "-5-6" );
    EXPECT_EQ ( -402, command.addcredits ( arg ) );
}
//Add Credits Bad Args
TEST ( addCreditsTest, BadArgAmt )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "addcredits" );
    arg.push_back ( accountName );
    arg.push_back ( "5" );
    arg.push_back ( accountName );
    EXPECT_EQ ( -406, command.addcredits ( arg ) );
}
//############
//Add User
//###########
//Normal Add User
TEST ( addUserTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "adduser" );
    arg.push_back ( newUserName );
    EXPECT_EQ ( 0, command.adduser ( arg ) );
}
//Normal Add User/pass
TEST ( addUserTest, NormalPass )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "adduser" );
    arg.push_back ( newUserName );
    arg.push_back ( newUserPass );
    EXPECT_EQ ( 0, command.adduser ( arg ) );
    //TODO: after this, check to see if it is now a valid user
}
//Add User, No admin
TEST ( addUserTest, NoAdmin )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "adduser" );
    arg.push_back ( newUserName );
    EXPECT_EQ ( -200, command.adduser ( arg ) );
}
//Add User, dup username
TEST ( addUserTest, DupUser )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "adduser" );
    arg.push_back ( accountName );
    EXPECT_EQ ( -412, command.adduser ( arg ) );
}
//Add User Bad Args
TEST ( addUserTest, BadArgAmt )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "adduser" );
    arg.push_back ( newUserName );
    arg.push_back ( newUserPass );
    arg.push_back ( newUserName );
    EXPECT_EQ ( -406, command.adduser ( arg ) );
}
//******************************
// Edit Slot Tests
//******************************
//EDITSLOT <slotnum> <name> <cost> <quantity> <num_dropped> <enabled>
//Edit Slot Normal
TEST ( editSlotTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "editslot" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "\"coca cola\"" );
    arg.push_back ( "5" );
    arg.push_back ( "5" );
    arg.push_back ( "2" );
    arg.push_back ( "true" );
    EXPECT_EQ ( 0, command.editslot ( arg ) );
}
//Edit Slot Invalid Slot
TEST ( editSlotTest, InvalidSlot )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "editslot" );
    arg.push_back ( invalidSlotNum );
    arg.push_back ( "\"coca cola\"" );
    arg.push_back ( "5" );
    arg.push_back ( "5" );
    arg.push_back ( "2" );
    arg.push_back ( "true" );
    EXPECT_EQ ( -409, command.editslot ( arg ) );
}
//Edit Slot Invalid Name
TEST ( editSlotTest, InvalidName )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "editslot" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "cocacola" );
    arg.push_back ( "5" );
    arg.push_back ( "5" );
    arg.push_back ( "2" );
    arg.push_back ( "true" );
    EXPECT_EQ ( -406, command.editslot ( arg ) );
}
//Edit Slot Invalid Cost
TEST ( editSlotTest, InvalidCost )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "editslot" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "\"coke\"" );
    arg.push_back ( "sdfadsf" );
    arg.push_back ( "5" );
    arg.push_back ( "2" );
    arg.push_back ( "true" );
    EXPECT_EQ ( -401, command.editslot ( arg ) );
}
//Edit Slot Invalid Quantity
TEST ( editSlotTest, InvalidQuantity )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "editslot" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "\"coke\"" );
    arg.push_back ( "20" );
    arg.push_back ( "asfd" );
    arg.push_back ( "2" );
    arg.push_back ( "true" );
    EXPECT_EQ ( -408, command.editslot ( arg ) );
}
//Edit slot Invalid Num Dropped
TEST ( editSlotTest, InvalidNumDropped )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "editslot" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "\"coke\"" );
    arg.push_back ( "20" );
    arg.push_back ( "10" );
    arg.push_back ( "sdasdf" );
    arg.push_back ( "true" );
    EXPECT_EQ ( -405, command.editslot ( arg ) );
}
//Edit slot Invalid enable flag
TEST ( editSlotTest, InvalidEnableFlag )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "editslot" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "\"coke\"" );
    arg.push_back ( "20" );
    arg.push_back ( "10" );
    arg.push_back ( "5" );
    arg.push_back ( "bab" );
    EXPECT_EQ ( -404, command.editslot ( arg ) );
}
//Edit slot Invalid Parameters
TEST ( editSlotTest, InvalidParams )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "editslot" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "\"coke\"" );
    arg.push_back ( "20" );
    arg.push_back ( "10" );
    arg.push_back ( "5" );
    arg.push_back ( "true" );
    arg.push_back ( "babgrg" );
    EXPECT_EQ ( -406, command.editslot ( arg ) );
}
//Edit slot not admin
TEST ( editSlotTest, NotAdmin )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "editslot" );
    arg.push_back ( validSlotNum );
    arg.push_back ( "\"coke\"" );
    arg.push_back ( "20" );
    arg.push_back ( "10" );
    arg.push_back ( "5" );
    arg.push_back ( "true" );
    EXPECT_EQ ( -200, command.editslot ( arg ) );
}
//******************************
// Edit User Tests
//******************************
//EDITUSER <username> <credits>[admin]
//Edit User Normal
TEST ( editUserTest, Normal )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "edituser" );
    arg.push_back ( accountName );
    arg.push_back ( "5" );
    EXPECT_EQ ( 0, command.edituser ( arg ) );
}
TEST ( editUserTest, NormalNegCredits )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "edituser" );
    arg.push_back ( accountName );
    arg.push_back ( "-5" );
    EXPECT_EQ ( 0, command.edituser ( arg ) );
}
//Edit User Set Admin
TEST ( editUserTest, NormalSetAdmin )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "edituser" );
    arg.push_back ( accountName );
    arg.push_back ( "5" );
    arg.push_back ( "true" );
    EXPECT_EQ ( 0, command.edituser ( arg ) );
}
//TODO: Add a test for removing admin
//Edit User Invalid User
TEST ( editUserTest, InvalidUser )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "edituser" );
    arg.push_back ( invalidAccountName );
    arg.push_back ( "5" );
    EXPECT_EQ ( -410, command.edituser ( arg ) );
}
//Edit User Invalid Credits
TEST ( editUserTest, InvalidCredits )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "edituser" );
    arg.push_back ( accountName );
    arg.push_back ( "asdfdfs" );
    EXPECT_EQ ( -402, command.edituser ( arg ) );
}
//Edit User Invalid Admin Flag
TEST ( editUserTest, InvalidAdminFlag )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "edituser" );
    arg.push_back ( accountName );
    arg.push_back ( "5" );
    arg.push_back ( "grg" );
    EXPECT_EQ ( -400, command.edituser ( arg ) );
}
//Edit User Invalid Parameters
TEST ( editUserTest, InvalidParam )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "edituser" );
    arg.push_back ( accountName );
    arg.push_back ( "5" );
    arg.push_back ( "true" );
    arg.push_back ( "grg" );
    EXPECT_EQ ( -406, command.edituser ( arg ) );
}
//Edit User Not authenticated
TEST ( editUserTest, NotAdmin )
{
      Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "edituser" );
    arg.push_back ( accountName );
    arg.push_back ( "5" );
    EXPECT_EQ ( -200, command.edituser ( arg ) );
}
//*****************
// IsValidUser
//*****************
//ISVALIDUSER <user>
//Normal test, should pass with success
TEST ( isValidUserTest, Normal )
{
     Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "isvaliduser" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.isvaliduser ( arg ) );
}
//Too many arguments
TEST ( isValidUserTest, TooManyArgs )
{
     Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "isvaliduser" );
    arg.push_back ( accountName );
    arg.push_back ( accountName );
    EXPECT_EQ ( -406, command.isvaliduser ( arg ) );
}
//Too few arguments
TEST ( isValidUserTest, TooFewArgs )
{
     Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "isvaliduser" );
    EXPECT_EQ ( -406, command.isvaliduser ( arg ) );
}
//Non admin
TEST ( isValidUserTest, NonAdmin )
{
     Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "isvaliduser" );
    arg.push_back ( accountName );
    EXPECT_EQ ( -200, command.isvaliduser ( arg ) );
}
//*****************
// Log
//*****************
TEST ( logTest, Normal )
{
     Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "log" );
    EXPECT_EQ ( 0, command.log ( arg ) );
}
//Test non admin users
TEST ( logTest, NonAdmin )
{
     Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "log" );
    EXPECT_EQ ( -200, command.log ( arg ) );
}
//*****************
// QueryAdmin
//*****************
//QUERYADMIN <user>
//Normal Test
TEST ( queryAdminTest, Normal )
{
     Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "queryadmin" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.queryadmin ( arg ) );
}
//Not Admin Test
TEST ( queryAdminTest, NonAdmin )
{
     Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( accountName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( accountPw );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "queryadmin" );
    arg.push_back ( accountName );
    EXPECT_EQ ( -200, command.queryadmin ( arg ) );
}
//Invalid User Test
TEST ( queryAdminTest, InvalidUser )
{
     Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "queryadmin" );
    arg.push_back ( invalidAccountName );
    EXPECT_EQ ( -410, command.queryadmin ( arg ) );
}
//Invalid Num of Params
TEST ( queryAdminTest, InvalidNumParams )
{
     Command::Command command ( 0, machineName, 0 );
    vector<string> arg;
    arg.push_back ( "user" );
    arg.push_back ( adminName );
    EXPECT_EQ ( 0, command.user ( arg ) );
    arg.clear();
    arg.push_back ( "pass" );
    arg.push_back ( adminPassword );
    EXPECT_EQ ( 0, command.pass ( arg ) );
    arg.clear();
    arg.push_back ( "queryadmin" );
    arg.push_back ( accountName );
    arg.push_back ( accountName );
    EXPECT_EQ ( -406, command.queryadmin ( arg ) );
}
//*****************
// RmUser
//*****************
//RMUSER <user>
//Normal Test

//*****************
// Set Admin
//*****************

//*****************
// Shutdown
//*****************

//Runs all the tests
int main ( int argc, char **argv )
{
    ::testing::InitGoogleTest ( &argc, argv );
    return RUN_ALL_TESTS();
}

