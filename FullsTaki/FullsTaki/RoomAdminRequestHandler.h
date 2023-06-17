#pragma once
#include "incs.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "ServerData.h"

class RequestHandlerFactory;
class RoomAdminRequestHandler : public IRequestHandler {


public:
    virtual bool isRequestRelevant(const RequestInfo request) const override;
    virtual RequestResult handleRequest(const RequestInfo request) const override;
    RoomAdminRequestHandler(Room* room, LoggedUser* user, RoomManager* roomManager, RequestHandlerFactory* handlerFactory);
    RoomAdminRequestHandler(const string username, const SOCKET socket, RoomManager& roomManager, RequestHandlerFactory& factory, const int roomId);
private:
    RequestResult closeRoom(RequestInfo request) const;
    RequestResult startGame(RequestInfo request) const;
    RequestResult getRoomState(RequestInfo request) const;
    Room* m_room;
    LoggedUser* m_user;
    RoomManager* m_roomManager;
    RequestHandlerFactory* m_handlerFactory;
};
