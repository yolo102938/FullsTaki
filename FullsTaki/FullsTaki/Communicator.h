#pragma once
#include "ServerData.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"


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
