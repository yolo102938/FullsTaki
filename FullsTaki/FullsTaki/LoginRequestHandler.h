#pragma once
#include "IRequestHandler.h"
#include "jsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestTypes.hpp"

class LoginRequestHandler :public IRequestHandler
{
public:

	bool isRequestRelevant(const RequestInfo request) const override;

	RequestResult handleRequest(const RequestInfo request, const SOCKET sock) const override;

private:
	/* LATER VERSION I GUESS
	RequestResult login(const RequestInfo request, const SOCKET socket) const;
	RequestResult signup(const RequestInfo request) const;

	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
	*/
};