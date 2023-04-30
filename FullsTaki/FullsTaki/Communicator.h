#pragma once
#include <map>
#include <windows.h>
#include "RequestHandlerFactory.h"
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
	map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;
};
