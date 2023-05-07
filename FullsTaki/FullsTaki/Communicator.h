#pragma once

//#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#define PORT_NUM 888



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
};
