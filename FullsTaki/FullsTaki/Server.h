#pragma once
#include "Communicator.h"
#include "incs.h"


class Server
{
public:
	Server(IDatabase* database);
	~Server();
	void run();
private:
	IDatabase* m_database;
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
}; 
