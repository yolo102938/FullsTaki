#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(const string username, const SOCKET socket, RoomManager& roomManager, RequestHandlerFactory& factory, const int roomId)
{
	m_user = new LoggedUser(username, socket);
	m_roomManager = &roomManager;
	m_handlerFactory = &factory;
	m_room = &(roomManager.getRoom(roomId));
}


bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo request) const
{
	return (request.id == LEAVE_ROOM) || (request.id == GET_ROOM_STATE || request.id == LOGOUT || request.id == GET_ROOMS);
}


RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo request) const
{
	try
	{
		try
		{
			cout << "Member Is Active: ";
			cout << &m_room->m_metadata.isActive << " --> " << m_room->m_metadata.isActive << endl;
		}
		catch (...)
		{ }
		if (request.id == LEAVE_ROOM)
		{
			return this->leaveRoom(request);
		}
		
		else if (request.id == GET_ROOM_STATE)
		{
			return this->getRoomState(request);
		}

		else if (request.id == START_GAME || request.id == GET_GAME_STATE)
		{
			return startGame(request);
		}
	}

	catch (nlohmann::json::exception& e)
	{
		ErrorResponse res = { "ERROR: Request contains invalid json" };
		return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	}

	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	}
}


RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo request) const
{
	LeaveRoomResponse res = { LEAVE_ROOM_RESPONSE };

	this->m_roomManager->getRoom(this->m_room->getRoomData().id).removeUser(*(this->m_user));

	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler(this->m_user) };
}


RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo request) const
{
	GetRoomStateResponse res = { GET_ROOM_STATE_RESPONSE,
		this->m_roomManager->getRoomState(this->m_room->getRoomData().id),
		this->m_room->getAllUsers()};

	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createRoomMemberRequestHandler(this->m_user->getUsername(), this->m_user->getSocket(), this->m_room->getRoomData().id, m_roomManager) };
}

RequestResult RoomMemberRequestHandler::startGame(RequestInfo request) const
{
	//StartGameResponse res = { START_GAME_RESPONSE };

	map<SOCKET, IRequestHandler*>& clients = Communicator::m_clients_stat;

	Game& current_game = this->m_handlerFactory->getGameManager().getGame(this->m_room->m_metadata.id);

	for (auto& user : this->m_room->m_users)
	{
		clients[user.getSocket()] = this->m_handlerFactory->createGameRequestHandler(user.getUsername(), user.getSocket(), current_game);
		StartGameResponse start_game_res = { START_GAME_RESPONSE };
		vector<char> serialized_res = JsonResponsePacketSerializer::serializeResponse(start_game_res);
		sendData(user.getSocket(), serialized_res);
	}

	this->m_room->m_metadata.isActive = true;

	//return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory->createGameRequestHandler(this->m_user->getUsername(), this->m_user->getSocket(), current_game) };

	return { JsonResponsePacketSerializer::serializeResponse(current_game.getGameStatus()), clients[this->m_user->getSocket()] };
}

void RoomMemberRequestHandler::sendData(SOCKET sc, vector<char> message) const
{
	if (send(sc, reinterpret_cast<const char*>(message.data()), message.size(), 0) == SOCKET_ERROR)
	{
		throw exception("Error while sending message to client");
	}
}