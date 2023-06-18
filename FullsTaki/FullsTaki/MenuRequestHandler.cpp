#include "MenuRequestHandler.h"

bool MenuRequestHandler::isRequestRelevant(RequestInfo request) const
{
    return request.id == LOGOUT || request.id == GET_ROOMS || request.id == CREATE_ROOM || request.id == JOIN_ROOM || request.id == GET_USERS_IN_ROOM || request.id == GET_ROOM_STATE;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo request) const
{
    RequestResult ret;//temp, will delete before returning
    try
    {
        if (request.id == LOGOUT)
        {
           ret = logout(request);
        }
        else if (request.id == GET_ROOMS)
        {
            ret = getRooms(request);
        }
        else if (request.id == GET_USERS_IN_ROOM)
        {
            ret = getPlayersInRoom(request);
        }
        else if (request.id == JOIN_ROOM)
        {
           ret = joinRoom(request);
        }
        else if (request.id == CREATE_ROOM)
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


RequestResult MenuRequestHandler::logout(const RequestInfo request) const
{
    LoginRequest req = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
    LoginRequestHandler* temp = new LoginRequestHandler(*m_handlerFactory);
    temp->m_loginManager.logout(req.username);
    LogoutResponse res = { LOGOUT_RESPONSE };
    return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createLoginRequestHandler() };
}

RequestResult MenuRequestHandler::getRooms(RequestInfo request) const
{
    GetRoomsResponse res = { GET_ROOMS_RESPONSE, this->m_roomManager->getRooms() };
    return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(this->m_user->getUsername(), this->m_user->getSocket()) };
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
    JoinRoomRequest req = JsonRequestPacketDeserializer::desirializeJoinRoom(request.buffer);
    ErrorResponse error_res;
    if (this->m_roomManager->hasRoom(req.roomId)) // check if room exist
    {
        if (this->m_roomManager->getRoom(req.roomId).getRoomData().maxPlayers > this->m_roomManager->getRoom(req.roomId).getAllUsers().size()) // check if room isn't full
        {
            this->m_roomManager->getRoom(req.roomId).addUser(*this->m_user);

            JoinRoomResponse res = { JOIN_ROOM_RESPONSE };
            return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createRoomMemberRequestHandler(this->m_user->getUsername(), this->m_user->getSocket(), req.roomId) };
        }

        else
            error_res = { "Room is full!" };
    }

    else
        error_res = { "Room doesn't exist" };

    return { JsonResponsePacketSerializer::serializeResponse(error_res), (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(this->m_user->getUsername(), this->m_user->getSocket()) };
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo request) const
{

    CreateRoomRequest req = JsonRequestPacketDeserializer::deserializeCreateRoom(request.buffer);

    if (req.maxUsers > 1)
    {
        RoomData room_data = { 0, req.roomName, req.maxUsers, true, 10 };
        this->m_roomManager->createRoom(*this->m_user, room_data);
        CreateRoomResponse res = { CREATE_ROOM_RESPONSE };
        return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createRoomAdminRequestHandler(this->m_user->getUsername(), this->m_user->getSocket(), room_data.id, this->m_roomManager) };
    }

    ErrorResponse error_res = { "Error creating room" }; // get the proper error message

    return { JsonResponsePacketSerializer::serializeResponse(error_res), (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(this->m_user->getUsername(), this->m_user->getSocket()) };
}

