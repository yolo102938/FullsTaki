#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& factory) :
	IRequestHandler(), m_handlerFactory(factory), m_loginManager(factory.getLoginManager())
{}

LoginRequestHandler::~LoginRequestHandler()
{}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo request) const
{
	return (request.id == LOGIN) || (request.id == SIGN_UP || request.id == GET_ROOMS || request.id == GET_ROOM_STATE); //checking if the request is for login/signup processing.
}


RequestResult LoginRequestHandler::handleRequest(const RequestInfo request) const
{
	RequestResult res;//temp, will delete before returning
	return res;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo request, SOCKET sock) const
{
	RequestResult res;//temp, will delete before returning
	try
	{
		if (request.id == LOGIN)
		{

			res = login(request, sock);
		}

		else if (request.id == SIGN_UP)
		{
			res = signup(request, sock);

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
RequestResult LoginRequestHandler::login(const RequestInfo request, SOCKET sock) const
{
	LoginRequest req = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
	this->m_loginManager.login(req.username, req.password, sock);
	LoginResponse res = { LOGIN_RESPONSE };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(new LoggedUser{req.username, sock}) };
}

RequestResult LoginRequestHandler::signup(const RequestInfo request, SOCKET sock) const
{
	SignupRequest req = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
	//std::cout << req.username, req.password, req.email;
	this->m_loginManager.signup(req.username, req.password, req.email, sock);
	SignupResponse res = { SIGNUP_RESPONSE };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createLoginRequestHandler() };
}
