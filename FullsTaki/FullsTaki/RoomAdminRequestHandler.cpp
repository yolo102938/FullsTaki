#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room* room, LoggedUser* user, RoomManager* roomManager, RequestHandlerFactory* handlerFactory) {
    m_room = room;
    m_user = user;
    m_roomManager = roomManager;
    m_handlerFactory = handlerFactory;
}

RoomAdminRequestHandler::RoomAdminRequestHandler(const string username, const SOCKET socket, RoomManager& roomManager, RequestHandlerFactory& factory, const int roomId)
{
    m_user = new LoggedUser(username, socket);
    m_roomManager = new RoomManager(roomManager);
    m_handlerFactory = &factory;
    m_room = new Room(roomManager.getRoom(roomId));
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo request) const {
    return(request.id == CLOSE_ROOM || request.id == START_GAME || request.id == GET_ROOM_STATE || request.id == LOGOUT || request.id == GET_ROOMS);
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo request)  const {
    RequestResult ret;//temp, will delete before returning
    try
    {
        if (request.id == CLOSE_ROOM) {
            ret =  closeRoom(request);
        }

        else if (request.id == START_GAME) {
            ret = startGame(request);
        }
        if (request.id == GET_ROOM_STATE) {
            ret =  getRoomState(request);
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

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo request) const
{
    CloseRoomResponse res = { CLOSE_ROOM_RESPONSE };

    for (auto& user : this->m_room->m_users)
    {
        LeaveRoomResponse leave_res = { LEAVE_ROOM_RESPONSE };

        this->m_roomManager->getRoom(this->m_room->getRoomData().id).removeUser(user);


        vector<char> serialized_res = JsonResponsePacketSerializer::serializeResponse(leave_res);
        string serizlized_res_str(serialized_res.begin(), serialized_res.end());
        //sendData(user.(), serizlized_res_str);
    }
    this->m_roomManager->deleteRoom(this->m_room->getRoomData().id);

    return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(this->m_user->getUsername(), this->m_user->getSocket()) };

}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo request) const
{
    StartGameResponse ret = { GENERIC_OK };
    return { JsonResponsePacketSerializer::serializeResponse(ret) ,m_handlerFactory->createMenuRequestHandler(m_user) };
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo request) const{
    GetRoomStateResponse res = { GET_ROOM_STATE_RESPONSE,
        this->m_roomManager->getRoomState(this->m_room->getRoomData().id),
        this->m_room->getAllUsers()};

    return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createRoomAdminRequestHandler(this->m_user->getUsername(), this->m_user->getSocket(), this->m_room->getRoomData().id) };

}
