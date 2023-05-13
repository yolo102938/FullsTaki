#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo request) const
{
	std::cout << request.id;
	return (request.id == LOGIN_REQUEST) || (request.id == SIGNUP_REQUEST); //checking if the request is for login/signup processing.
}


RequestResult LoginRequestHandler::handleRequest(const RequestInfo request, const SOCKET socket) const
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

