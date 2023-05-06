#pragma once
#include "Communicator.h"



Communicator::Communicator()
{
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(m_serverSocket);
	}
	catch (...) {}
}

void Communicator::handleNewClient(SOCKET clientSocket)
{

	std::cout << "Client accepted !" << std::endl;
	std::string msg = "HELLO";
	bool active = true;
	bool alrin = true;
	try
	{
		int code = 0;
		int size = 0;

		while (active) {
			char* data = new char[msg.length() + 1];
			int res = recv(clientSocket, data, msg.length() + 1, 0);
			if (res == INVALID_SOCKET)
			{
				std::string s = "Error while recieving from socket: ";
				throw std::exception(s.c_str());
			}
			data[msg.length()] = 0;
			std::string received(data);
			if (msg != received)
			{
				std::string s = "Not HELLO but "+received;
				throw std::exception(s.c_str());
			}
			if (alrin) {
				this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(clientSocket, new IRequestHandler()));
				alrin = false;
			}
			const char* _data = msg.c_str();

			if (send(clientSocket, _data, msg.size(), 0) == INVALID_SOCKET)
			{
				throw std::exception("Error while sending message to client");
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was catched in function communicator. socket = " << clientSocket << ", what = " << e.what() << "\n Logging out."<<std::endl;
		closesocket(clientSocket);
		m_clients.erase(clientSocket);
	}

}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT_NUM); // port that server will listen to
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;  // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	std::cout << "binded" << std::endl;
	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT_NUM << std::endl;
}

void Communicator::startHandleRequests() 
{
	bindAndListen();
	while (true)
	{
		printf("accepting client...\n");
		SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);
		std::thread handler(&Communicator::handleNewClient, this, client_socket);
		handler.detach();
	}
}


