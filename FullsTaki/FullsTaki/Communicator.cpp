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

Communicator::Communicator(RequestHandlerFactory& factory) : m_handlerFactory(factory)
{
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
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

			//If the client is not logged in, creating a new LoginRequestHandler instance and adding it to the clients map
			if (!isLoggedIn)
			{
				this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(socketClient, m_handlerFactory.createLoginRequestHandler()));
				isLoggedIn = false;
			}
			
			//Receiving the request code
			if (recv(socketClient, reinterpret_cast<char*>(&requestCode), sizeof(requestCode), 0) != sizeof(requestCode))
			{
				sendError(socketClient); //sending an error if the request code is not received correctly
			}
			requestCode = ntohl(requestCode);
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
			msgSize = ntohl(msgSize);
			//Creating a buffer to store the received data and receive the data
			std::vector<unsigned char> bufferData(msgSize);
			if (recv(socketClient, reinterpret_cast<char*>(bufferData.data()), msgSize, 0) != msgSize)
			{
				sendError(socketClient); //sending an error if the data is not received correctly
			}


			//Creating a RequestInfo object to store the received request information
			RequestInfo reqInfo = { requestCode, std::time(nullptr), bufferData };

			//Checking if the received request is relevant
			if (this->m_clients[socketClient]->isRequestRelevant(reqInfo))
			{
				//Processing the received request and obtaining the result
				RequestResult reqResult = this->m_clients[socketClient]->handleRequest(reqInfo);

				//Sending the response data
				if (send(socketClient,reqResult.response.data(), reqResult.response.size(), 0) == SOCKET_ERROR)
				{
					sendError(socketClient); //sending an error if the response data is not sent correctly
				}

				this->m_clients[socketClient] = reqResult.newHandler;
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
		LoginRequestHandler* clientHandler = m_handlerFactory.createLoginRequestHandler();
		m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, clientHandler));
		std::thread handler(&Communicator::handleNewClient, this, client_socket);
		handler.detach();
	}
}


