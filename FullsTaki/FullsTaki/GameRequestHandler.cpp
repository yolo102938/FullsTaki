#include "GameRequestHandler.h"


GameRequestHandler::GameRequestHandler(const string username, const SOCKET socket, GameManager& gameManager, RequestHandlerFactory& factory, Game& game) : m_user(username, socket), m_gameManager(gameManager), m_handlerFactory(factory), m_game(game)
{

}


bool GameRequestHandler::isRequestRelevant(const RequestInfo request) const
{
	return (request.id == PLAY_CARD) || (request.id == GET_ROOM_STATE);
}


RequestResult GameRequestHandler::handleRequest(const RequestInfo request) const
{
	try
	{

		if (request.id == PLAY_CARD)
		{
			return this->cardPlaydResponse(request);
		}

		else if (request.id == GET_ROOM_STATE)
		{
			return { vector<char>(), this->m_handlerFactory.createGameRequestHandler(this->m_user.getUsername(), this->m_user.getSocket(), this->m_gameManager.getGame(this->m_game.getGameId())) };
		}

	}

	catch (nlohmann::json::exception& e)
	{
		ErrorResponse res = { "ERROR: The request contains invalid json data" };
		return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	}

	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	}

	return { vector<char>(), this->m_handlerFactory.createGameRequestHandler(this->m_user.getUsername(), this->m_user.getSocket(), this->m_gameManager.getGame(this->m_game.getGameId())) };
}


RequestResult GameRequestHandler::cardPlaydResponse(const RequestInfo request) const
{
	PlaceCardRequest req = JsonRequestPacketDeserializer::deserializePlayCardRequest(request.buffer);

	this->m_gameManager.getGame(this->m_game.getGameId()).playCard(this->m_user, req.cardId);

	PlaceCardResponse res = { SUCCESS_RESPONSE };

	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createGameRequestHandler(this->m_user.getUsername(), this->m_user.getSocket(), this->m_gameManager.getGame(this->m_game.getGameId())) };

}
