#pragma once
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"
#include "GameManager.h"
#include "IRequestHandler.h"
#include "jsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestTypes.hpp"
#include "ResponseTypes.hpp"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "ServerData.h"
#include <mutex>

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:

	//constructor
	GameRequestHandler(const string username, const SOCKET socket, GameManager& gameManager, RequestHandlerFactory& factory, Game& game);

	//overloaded functions of the class IRequestHandler.
	bool isRequestRelevant(const RequestInfo request) const override;
	RequestResult handleRequest(const RequestInfo request) const override;

	//function returns a response after playing the card.
	RequestResult cardPlaydResponse(const RequestInfo request) const;
private:

	LoggedUser m_user;
	Game& m_game;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;
	mutable mutex mutexUsersCounter;
};