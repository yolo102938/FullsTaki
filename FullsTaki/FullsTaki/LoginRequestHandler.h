#pragma once
#include "IRequestHandler.h"
#include "jsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestTypes.hpp"
#include "RequestHandlerFactory.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& factory);

	~LoginRequestHandler();

	virtual bool isRequestRelevant(const RequestInfo request) const override;

	virtual RequestResult handleRequest(const RequestInfo request) const override;

	RequestResult login(const RequestInfo request) const;

	RequestResult signup(const RequestInfo request) const;

private:

	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
};