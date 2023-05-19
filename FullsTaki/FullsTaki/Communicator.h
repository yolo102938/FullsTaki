#pragma once

#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"

#define PORT_NUM 888
#define IP_ADDR "1.1.1.1"

using std::map;

class Communicator
{
	public:
		Communicator(RequestHandlerFactory& factory);;
		~Communicator();
		void startHandleRequests();
		void bindAndListen();
		void handleNewClient(SOCKET);
	private:
		SOCKET m_serverSocket;
		map<SOCKET, IRequestHandler*> m_clients;
		RequestHandlerFactory& m_handlerFactory;
};
