#pragma once
#include "ServerData.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"


using std::map;

class Communicator
{
	public:
		static Communicator& staticInstance(RequestHandlerFactory& factory_handle)
		{
			static Communicator instance(factory_handle);
			return instance;
		}
		Communicator(RequestHandlerFactory& factory);
		~Communicator();
		void startHandleRequests();
		void bindAndListen();
		void handleNewClient(SOCKET);
		map<SOCKET, IRequestHandler*> m_clients;
	private:
		SOCKET m_serverSocket;
		RequestHandlerFactory& m_handlerFactory;
		int GetMsgCode(const SOCKET socket) const;
		int GetDataLength(const SOCKET socket) const;
		vector<unsigned char> GetMsgData(const SOCKET socket, const int length) const;
};
