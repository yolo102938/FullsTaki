#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(const string username, const SOCKET socket, RoomManager& roomManager, RequestHandlerFactory& factory, const int roomId) : m_user(username, socket), m_roomManager(roomManager), m_handlerFactory(factory), m_room(roomManager.getRoom(roomId))
{}


bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo request) const
{
	return (request.id == LEAVE_ROOM) || (request.id == GET_ROOM_STATE);
}


RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo request) const
{
	try
	{
		if (request.id == LEAVE_ROOM)
		{
			return this->leaveRoom(request);
		}

		else if (request.id == GET_ROOM_STATE)
		{
			return this->getRoomState(request);
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

	this->m_roomManager.getRoom(this->m_room.getRoomData().id).removeUser(this->m_user);

	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(&this->m_user) };
}


RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo request) const
{
	if (this->m_roomManager.hasRoom(this->m_room.getRoomData().id))
	{
		GetRoomStateResponse res = { GET_ROOM_STATE, this->m_roomManager.getRoomState(this->m_room.getRoomData().id), this->m_room.getAllUsers()};

		return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user.getUsername(), this->m_user.getSocket(), this->m_room.getRoomData().id) };
	}
	else
	{
		vector<char> null_packet;
		null_packet.push_back(static_cast<unsigned char>(' '));
		return { null_packet, (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(&this->m_user) };
	}
}
