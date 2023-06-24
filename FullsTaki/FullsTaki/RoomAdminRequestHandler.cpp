#include "RoomAdminRequestHandler.h"
#include "Communicator.h"

void sendData(SOCKET sc, vector<char> message);

RoomAdminRequestHandler::RoomAdminRequestHandler(Room* room, LoggedUser* user, RoomManager& roomManager, RequestHandlerFactory* handlerFactory)
{
    m_room = room;
    m_user = user;
    m_roomManager = &roomManager;
    m_handlerFactory = handlerFactory;
}

RoomAdminRequestHandler::RoomAdminRequestHandler(const string username, const SOCKET socket, RoomManager& roomManager, RequestHandlerFactory& factory, const int roomId)
{
    m_user = new LoggedUser(username, socket);
    m_roomManager = &roomManager;
    m_handlerFactory = &factory;
    m_room = &(roomManager.getRoom(roomId));
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo request) const
{
    return(request.id == CLOSE_ROOM || request.id == START_GAME || request.id == GET_ROOM_STATE || request.id == LOGOUT || request.id == GET_ROOMS);
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo request)  const
{
    RequestResult ret;
    try
    {
        try
        {
            cout << "Admin Is Active: ";
            cout << &m_room->m_metadata.isActive << " --> " << m_room->m_metadata.isActive << endl;
        }
        catch (...)
        {
        }
        if (request.id == CLOSE_ROOM)
        {
            ret =  closeRoom(request);
        }

        else if (request.id == START_GAME)
        {
            ret = startGame(request);
        }

        else if (request.id == GET_ROOM_STATE)
        {
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
        sendData(user.getSocket(), serialized_res);
    }
    this->m_roomManager->deleteRoom(this->m_room->getRoomData().id);

    return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(this->m_user->getUsername(), this->m_user->getSocket()) };

}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo request) const
{
    GetRoomStateResponse res = { GET_ROOM_STATE_RESPONSE,
        this->m_roomManager->getRoomState(this->m_room->getRoomData().id),
        this->m_room->getAllUsers() };
    //cout << std::to_string(this->m_user->getSocket());
    return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createRoomAdminRequestHandler(this->m_user->getUsername(), this->m_user->getSocket(), this->m_room->getRoomData().id) };
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo request) const
{
    StartGameResponse res = { START_GAME_RESPONSE };

    map<SOCKET, IRequestHandler*>& clients = Communicator::m_clients_stat;

    Game& current_game = this->m_handlerFactory->getGameManager().createGame(this->m_user, *this->m_room);

    for (auto& user : this->m_room->m_users)
    {
        clients[user.getSocket()] = this->m_handlerFactory->createGameRequestHandler(user.getUsername(), user.getSocket(), current_game);

        StartGameResponse start_game_res = { START_GAME_RESPONSE };
        vector<char> serialized_res = JsonResponsePacketSerializer::serializeResponse(start_game_res);
        sendData(user.getSocket(), serialized_res);
    }

    this->m_room->m_metadata.isActive = true;

    return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createGameRequestHandler(this->m_user->getUsername(), this->m_user->getSocket(), current_game) };
}

void sendData(SOCKET sc, vector<char> message)
{
    if (send(sc, reinterpret_cast<const char*>(message.data()), message.size(), 0) == SOCKET_ERROR)
    {
        throw exception("Error while sending message to client");
    }
}