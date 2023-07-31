#include "RoomRequestHandler.h"

RoomRequestHandler::RoomRequestHandler(Room* room, LoggedUser* user, RoomManager* roomManager, RequestHandlerFactory* handlerFactory) {
    m_room = room;
    m_user = user;
    m_roomManager = roomManager;
    m_handlerFactory = handlerFactory;
}

bool RoomRequestHandler::isRequestRelevant(RequestInfo request) const {
    return(request.id == LEAVE_ROOM || request.id == GET_ROOM_STATE || request.id == LOGOUT || request.id == GET_ROOMS);
}

RequestResult RoomRequestHandler::handleRequest(RequestInfo request)  const {
    RequestResult ret;//temp, will delete before returning
    try
    {
        if (request.id == LEAVE_ROOM)
        {
            ret = leaveRoom(request);
        }
        if (request.id == GET_ROOM_STATE)
        {
            ret = getRoomState(request);
        }
    }

    //if an error occured, returning a RequestResult with the error's info.
    catch (exception& e)
    {
        ErrorResponse res = { e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this };
    }
    return ret;

}

RequestResult RoomRequestHandler::leaveRoom(RequestInfo request) const {
    m_roomManager->deleteRoom(m_room->getRoomData().id);
    CloseRoomResponse ret = { GENERIC_OK };
    return { JsonResponsePacketSerializer::serializeResponse(ret) ,m_handlerFactory->createMenuRequestHandler(m_user) };
}


RequestResult RoomRequestHandler::getRoomState(RequestInfo request) const {
    try {
        GetRoomStateResponse ret;
        RoomData data = m_room->getRoomData();
        ret.hasGameBegun = data.isActive;
        std::vector<std::string> users;
        for (auto user : m_room->getAllUsers()) {
            if (user != m_user->getUsername()) {//just so the list doesnt contain curr player
                users.push_back(user);
            }
        }
        ret.players = users;
        return { JsonResponsePacketSerializer::serializeResponse(ret) ,m_handlerFactory->createRoomRequestHandler(m_room,m_user) };
    }
    catch (const std::exception& e)
    {
        ErrorResponse ret = { "Room closed" };
        return { JsonResponsePacketSerializer::serializeResponse(ret) ,m_handlerFactory->createMenuRequestHandler(m_user) };
        try {
            m_roomManager->deleteRoom(m_room->getRoomData().id);
        }
        catch (...) {}
    }
}
