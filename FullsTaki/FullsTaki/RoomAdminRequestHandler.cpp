#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room* room, LoggedUser* user, RoomManager* roomManager, RequestHandlerFactory* handlerFactory) {

    m_room = room;
    m_user = user;
    m_roomManager = roomManager;
    m_handlerFactory = handlerFactory;

}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo request) const {

    return(request.id == CLOSEROOM_REQUEST || request.id == STARTGAME_REQUEST || request.id == GETROOMSTATE_REQUEST);
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo request)  const {
    RequestResult ret;//temp, will delete before returning
    try
    {
        if (request.id == CLOSEROOM_REQUEST) {
            ret =  closeRoom(request);
        }

        else if (request.id == STARTGAME_REQUEST) {
            ret = startGame(request);
        }
        if (request.id == GETROOMSTATE_REQUEST) {
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

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo request) const{
    m_roomManager->deleteRoom(m_room->getRoomData().id);
        CloseRoomResponse ret = { GENERIC_OK };
        return { JsonResponsePacketSerializer::serializeResponse(ret) ,m_handlerFactory->createMenuRequestHandler(m_user) };
    }

RequestResult RoomAdminRequestHandler::startGame(RequestInfo request) const{
    //for ohad to start game later
    StartGameResponse ret = { GENERIC_OK };
    return { JsonResponsePacketSerializer::serializeResponse(ret) ,m_handlerFactory->createMenuRequestHandler(m_user) };
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo request) const{
    try {
        
        GetRoomStateResponse ret;
        RoomData data = m_room->getRoomData();
        ret.hasGameBegun = data.isActive;
        std::vector<std::string> users;
        /*for (auto user : m_room->getAllUsers()) {
            if (user != m_user->getUsername()) {//just so the list doesnt contain curr player
                users.push_back(user);
            }
        }*/
        ret.players = m_room->getAllUsers();

        return { JsonResponsePacketSerializer::serializeResponse(ret) ,m_handlerFactory->createRoomAdminRequestHandler(m_room,m_user) };
    }
    catch (const std::exception& e)
    {
        ErrorResponse ret = { "Room closed" };
        return { JsonResponsePacketSerializer::serializeResponse(ret) ,m_handlerFactory->createMenuRequestHandler(m_user) };
        try{ 
            m_roomManager->deleteRoom(m_room->getRoomData().id);
        }
        catch (...) {}
    }
}
