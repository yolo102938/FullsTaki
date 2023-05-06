#include "WSAInitializer.h"
#include "Server.h"
int main(int argc, char** argv) {

	WSAInitializer wsaInit;
	try {
		Server srvr; //server setup
		srvr.run();//start running
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was catched, what = " << e.what() << std::endl;
	}



	return(0);
}