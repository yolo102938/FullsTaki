#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& factory) :
	IRequestHandler(), m_handlerFactory(factory), m_loginManager(factory.getLoginManager())
{}

LoginRequestHandler::~LoginRequestHandler()
{}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo request) const
{
	std::cout << request.id;
	return (request.id == LOGIN_REQUEST) || (request.id == SIGNUP_REQUEST); //checking if the request is for login/signup processing.
}


RequestResult LoginRequestHandler::handleRequest(const RequestInfo request) const
{
	LoginResponse res = { 0 };//temp, will delete before returning
	try
	{
		if (request.id == LOGIN_REQUEST)
		{
			JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer).print();//temp for v2
			LoginResponse res = { LOGIN_RESPONSE};
		}

		else if (request.id == SIGNUP_REQUEST)
		{
			JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer).print();//temp for v2
			SignupResponse res = { SIGNUP_RESPONSE };

		}
	}

	//if an error occured, returning a RequestResult with the error's info.
	catch (exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	}
	return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
}

RequestResult LoginRequestHandler::login(const RequestInfo request) const
{
	LoginRequest req = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
	this->m_loginManager.login(req.username, req.password);
	LoginResponse res = { LOGIN_RESPONSE };
	return { JsonResponsePacketSerializer::serializeResponse(res), /*LATER VERSION: forwarding menu handler after login i guess*/};
}


RequestResult LoginRequestHandler::signup(const RequestInfo request) const
{
	SignupRequest req = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
	this->m_loginManager.signup(req.username, req.password, req.email);
	SignupResponse res = { SIGNUP_RESPONSE };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createLoginRequestHandler() };
}