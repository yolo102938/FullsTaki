#pragma once
#include <iostream>
#include <exception>
#include <map>
#include <windows.h>
//#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"

#define PORT_NUM 80

using std::cout;
using std::endl;

class Communicator
{
public:
	Communicator();
	~Communicator();
	void startHandleRequests();
	void bindAndListen();
	void handleNewClient(SOCKET);
private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;
};
