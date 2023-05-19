#pragma once
#include "Server.h"

Server::Server(IDatabase* database) : 
	m_database(database), m_handlerFactory(RequestHandlerFactory(database)), m_communicator(Communicator(m_handlerFactory))
{}

Server::~Server()
{}

void Server::run()
{
	std::thread serve(&Communicator::startHandleRequests, std::ref(m_communicator));
	serve.detach();
	std::string inp = "h";
	while (inp!="EXIT")
	{
		std::cin>>inp;
	}

}

