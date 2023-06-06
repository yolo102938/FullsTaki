#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& factory) :
	IRequestHandler(), m_handlerFactory(factory), m_loginManager(factory.getLoginManager())
{}

LoginRequestHandler::~LoginRequestHandler()
{}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo request) const
{
	return (request.id == LOGIN_REQUEST) || (request.id == SIGNUP_REQUEST); //checking if the request is for login/signup processing.
}


RequestResult LoginRequestHandler::handleRequest(const RequestInfo request) const
{
	RequestResult res;//temp, will delete before returning
	try
	{
		if (request.id == LOGIN_REQUEST)
		{
			
			res = login(request);
		}

		else if (request.id == SIGNUP_REQUEST)
		{
			res = signup(request);

		}
	}

	//if an error occured, returning a RequestResult with the error's info.
	catch (exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createLoginRequestHandler() };
	}
	return res;
}

RequestResult LoginRequestHandler::login(const RequestInfo request) const
{
	LoginRequest req = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
	this->m_loginManager.login(req.username, req.password);
	LoginResponse res = { LOGIN_RESPONSE };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(new LoggedUser{req.username})};
}


RequestResult LoginRequestHandler::signup(const RequestInfo request) const
{
	SignupRequest req = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
	std::cout << req.username, req.password, req.email;
	this->m_loginManager.signup(req.username, req.password, req.email);
	SignupResponse res = { SIGNUP_RESPONSE };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createLoginRequestHandler() };
}