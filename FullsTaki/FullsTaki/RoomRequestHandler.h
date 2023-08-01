#pragma once
#include "incs.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class RoomRequestHandler : public IRequestHandler {


public:
    virtual bool isRequestRelevant(const RequestInfo request) const override;
    virtual RequestResult handleRequest(const RequestInfo request) const override;
    RoomRequestHandler(Room* room, LoggedUser* user, RoomManager* roomManager, RequestHandlerFactory* handlerFactory);

private:
    RequestResult leaveRoom(RequestInfo request) const;
    RequestResult getRoomState(RequestInfo request) const;
    Room* m_room;
    LoggedUser* m_user;
    RoomManager* m_roomManager;
    RequestHandlerFactory* m_handlerFactory;
};
