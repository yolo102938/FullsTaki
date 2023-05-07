#pragma once
#include "Server.h"

Server::Server()
{

	//m_communicator =  Communicator();
}

Server::~Server()
{

}

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

