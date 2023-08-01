
#include "MenuRequestHandler.h"

bool MenuRequestHandler::isRequestRelevant(RequestInfo request) const
{
    return request.id == LOGOUT_REQUEST || request.id == GETROOMS_REQUEST || request.id == CREATEROOM_REQUEST || request.id == JOINROOM_REQUEST || request.id == GETPARTICIPANTS_REQUEST;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo request) const
{
    RequestResult ret;//temp, will delete before returning
    try
    {
        if (request.id == LOGOUT_REQUEST)
        {
           ret = signout(request);
        }
        else if (request.id == GETROOMS_REQUEST)
        {
            ret = getRooms(request);
        }
        else if (request.id == GETPARTICIPANTS_REQUEST)
        {
            ret = getPlayersInRoom(request);
        }
        else if (request.id == JOINROOM_REQUEST)
        {
           ret = joinRoom(request);
        }
        else if (request.id == CREATEROOM_REQUEST)
        {
            ret = createRoom(request);
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


RequestResult MenuRequestHandler::signout(RequestInfo request) const 
{
    LoginResponse res = { GENERIC_OK };
    m_loginManager->logout(m_user->getUsername());
    for (auto room : m_roomManager->getRooms()) {
        for (auto user : m_roomManager->getRoom(room.id).getAllUsers()) {
            if (user == m_user->getUsername()) {
                m_roomManager->getRoom(room.id).removeUser(*m_user);
            }
        }
    }
    return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)m_handlerFactory->createLoginRequestHandler()};
}

RequestResult MenuRequestHandler::getRooms(RequestInfo request) const
{

    GetRoomsResponse res = {GENERIC_OK,this->m_roomManager->getRooms()};
    return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(m_user) };
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo request) const
{

    GetPlayersInRoomRequest req = JsonRequestPacketDeserializer::deserializeGetPlayersInRoom(request.buffer);
    
    GetPlayersInRoomResponse res = { this->m_roomManager->getRoom(req.roomId).getAllUsers() };
    return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(m_user) };
}
/*
RequestResult MenuRequestHandler::getPersonalStats(RequestInfo request) const
{
    
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo request) const
{
    
}
*/
RequestResult MenuRequestHandler::joinRoom(RequestInfo request) const
{
    JoinRoomResponse res = { GENERIC_OK };
    JoinRoomRequest req = JsonRequestPacketDeserializer::deserializeJoinRoom(request.buffer);
    int maxPlayers = this->m_roomManager->getRoom(req.roomId).getRoomData().maxPlayers;
    int currPlayers = this->m_roomManager->getRoom(req.roomId).getAllUsers().size();
    if(maxPlayers == currPlayers)
    {

        throw("Room is full!");
    }
    else if (this->m_roomManager->getRoom(req.roomId).getRoomData().isActive) {
        throw("Room is currently in a game!");
    }
    this->m_roomManager->getRoom(req.roomId).addUser(*m_user);
    return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(m_user) };
}

RequestResult MenuRequestHandler::createRoom(RequestInfo request) const
{
    CreateRoomResponse res = { GENERIC_OK };
    CreateRoomRequest req = JsonRequestPacketDeserializer::deserializeCreateRoom(request.buffer);
    
    this->m_roomManager->createRoom(*m_user, { static_cast<unsigned int>(this->m_roomManager->getRooms().size()) + 1, req.roomName,req.maxUsers,req.questionCount,0});
    return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(m_user) };
}

