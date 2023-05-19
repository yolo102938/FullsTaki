#pragma comment(lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include "Server.h"
#include "SqliteDataBase.h"
#include "IDatabase.h"
int main(int argc, char** argv)
{

	WSAInitializer wsaInit;
	try 
	{
		SqliteDataBase* db;
		db->open();
		Server* srvr = new Server(db); //server setup
		srvr->run();//start running
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was catched, what = " << e.what() << std::endl;
	}



	return(0);
}