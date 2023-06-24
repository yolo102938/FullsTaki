#pragma once
#include "IRequestHandler.h"
#include "jsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestTypes.hpp"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"
#include "Communicator.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(const string username, const SOCKET socket, RoomManager& roomManager, RequestHandlerFactory& factory, const int roomId);
	bool isRequestRelevant(const RequestInfo request) const override;
	RequestResult handleRequest(const RequestInfo request) const override;
private:

	RequestResult leaveRoom(const RequestInfo request) const;
	RequestResult getRoomState(const RequestInfo request) const;

	mutable Room* m_room;
	mutable LoggedUser* m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_handlerFactory;
};
