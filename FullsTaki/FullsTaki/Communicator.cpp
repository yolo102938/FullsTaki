#pragma once
#include "Communicator.h"
void sendError(SOCKET clientSocket) {
	int code = 0;
	if (send(clientSocket, reinterpret_cast<const char*>(&code), sizeof(code), 0) != sizeof(code))
	{
		throw std::exception("Error while sending response");
	}
	throw std::exception("Bad costumer");
}

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
/*
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
				std::string s = "Not HELLO but " + received;
				throw std::exception(s.c_str());
			}
			if (alrin) {
				this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(clientSocket, new LoginRequestHandler()));
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
		std::cout << "Exception was catched in function communicator. socket = " << clientSocket << ", what = " << e.what() << "\n Logging out." << std::endl;
		closesocket(clientSocket);
		m_clients.erase(clientSocket);
	}

}
*/
void Communicator::handleNewClient(SOCKET socketClient)
{
	//Notifying that a new client has been accepted
	std::cout << "Client accepted !" << std::endl;
	bool isActive = true; //Flag that indicates if the client's connection is still active
	bool isLoggedIn = false; //Flag that indicates if the client is logged in

	try
	{
		int requestCode = 0; //The received request code
		int msgSize = 0; //The received message size

		//Continuously process incoming messages in a loop while the connection is active
		while (isActive)
		{
			//Receiving the request code
			if (recv(socketClient, reinterpret_cast<char*>(&requestCode), sizeof(requestCode), 0) != sizeof(requestCode))
			{
				sendError(socketClient); //sending an error if the request code is not received correctly
			}

			//Ensuring the received request code is either LOGIN_REQUEST or SIGNUP_REQUEST if the client is not logged in
			if (requestCode != LOGIN_REQUEST && requestCode != SIGNUP_REQUEST && !isLoggedIn)
			{
				sendError(socketClient); //sending an error if the received request code is invalid
			}

			//Receiving the message size
			if (recv(socketClient, reinterpret_cast<char*>(&msgSize), sizeof(msgSize), 0) != sizeof(msgSize))
			{
				sendError(socketClient); //sending an error if the message size is not received correctly
			}

			//Creating a buffer to store the received data and receive the data
			std::vector<unsigned char> bufferData(msgSize);
			if (recv(socketClient, reinterpret_cast<char*>(bufferData.data()), msgSize, 0) != msgSize)
			{
				sendError(socketClient); //sending an error if the data is not received correctly
			}

			//If the client is not logged in, creating a new LoginRequestHandler instance and adding it to the clients map
			if (!isLoggedIn)
			{
				this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(socketClient, new LoginRequestHandler()));
				isLoggedIn = false;
			}
			else //If the client is logged in, updating the existing LoginRequestHandler instance
			{
				m_clients[socketClient] = new LoginRequestHandler();
			}

			//Creating a RequestInfo object to store the received request information
			RequestInfo reqInfo = { requestCode, std::time(nullptr), bufferData };

			//Checking if the received request is relevant
			if (this->m_clients[socketClient]->isRequestRelevant(reqInfo))
			{
				//Processing the received request and obtaining the result
				RequestResult reqResult = this->m_clients[socketClient]->handleRequest(reqInfo, socketClient);

				//Sending the response size
				int resSize = static_cast<int>(reqResult.response.size());
				if (send(socketClient, reinterpret_cast<const char*>(&resSize), sizeof(resSize), 0) != sizeof(resSize))
				{
					sendError(socketClient); //sending an error if the response size is not sent correctly
				}

				//Sending the response data
				if (send(socketClient, reqResult.response.data(), resSize, 0) != resSize)
				{
					sendError(socketClient); //sending an error if the response data is not sent correctly
				}
			}
			else
			{
				std::cout << "Not Relevant\n"; //printing a message if the received request is not relevant
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was caught in function communicator. socket = " << socketClient << ", what = " << e.what() << "\n Logging out." << std::endl;
		closesocket(socketClient);
		m_clients.erase(socketClient);
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


