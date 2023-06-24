#pragma once
#include "IRequestHandler.h"
#include "jsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestTypes.hpp"
#include "RequestHandlerFactory.h"
#include "ServerData.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& factory);

	~LoginRequestHandler();

	virtual bool isRequestRelevant(const RequestInfo request) const override;

	virtual RequestResult handleRequest(const RequestInfo request) const override;

	RequestResult handleRequest(const RequestInfo request, SOCKET sock) const;

	RequestResult login(const RequestInfo request, SOCKET sock) const;
	RequestResult signup(const RequestInfo request, SOCKET sock) const;
	LoginManager& m_loginManager;
private:

	RequestHandlerFactory& m_handlerFactory;
};