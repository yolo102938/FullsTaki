#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo request) const
{
	return (request.id == LOGIN_REQUEST) || (request.id == SIGNUP_REQUEST); //checking if the request is for login/signup processing.
}


RequestResult LoginRequestHandler::handleRequest(const RequestInfo request, const SOCKET socket) const
{
	try
	{
		if (request.id == LOGIN_REQUEST)
		{
			//LOGIN - TODO IN A LATER VERSION
		}

		else if (request.id == SIGNUP_REQUEST)
		{
			//SIGNUP - TODO IN A LATER VERSION
		}
	}

	//if an error occured, returning a RequestResult with the error's info.
	catch (exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	}
}

