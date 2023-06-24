#include "GameRequestHandler.h"


GameRequestHandler::GameRequestHandler(const string username, const SOCKET socket, GameManager& gameManager, RequestHandlerFactory& factory, Game& game) : m_user(username, socket), m_gameManager(gameManager), m_handlerFactory(factory), m_game(game)
{

}


bool GameRequestHandler::isRequestRelevant(const RequestInfo request) const
{
	return (request.id == PLAY_CARD) || (request.id == GET_ROOM_STATE) || (request.id == CARD_BANK_PREMISION) || (request.id == GET_GAME_STATE);
}


RequestResult GameRequestHandler::handleRequest(const RequestInfo request) const
{
	try
	{

		if (request.id == PLAY_CARD)
		{
			return this->playCardRequest(request);
		}

		else if (request.id == GET_ROOM_STATE)
		{
			return { vector<char>(), this->m_handlerFactory.createGameRequestHandler(this->m_user.getUsername(), this->m_user.getSocket(), this->m_gameManager.getGame(this->m_game.gameId)) };
		}

		else if (request.id == CARD_BANK_PREMISION)
		{
			return bankRequest();
		}

		else if (request.id == GET_GAME_STATE)
		{
			return gameState();
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

	return { vector<char>(), this->m_handlerFactory.createGameRequestHandler(this->m_user.getUsername(), this->m_user.getSocket(), this->m_gameManager.getGame(this->m_game.gameId)) };
}

/*
RequestResult GameRequestHandler::cardPlaydResponse(const RequestInfo request) const
{
	PlaceCardRequest req = JsonRequestPacketDeserializer::deserializePlayCardRequest(request.buffer);

	this->m_gameManager.getGame(this->m_game.gameId).playCard(this->m_user, req.cardId);

	PlaceCardResponse res = { SUCCESS_RESPONSE };

	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createGameRequestHandler(this->m_user.getUsername(), this->m_user.getSocket(), this->m_gameManager.getGame(this->m_game.gameId)) };

}*/

RequestResult GameRequestHandler::gameState() const
{
	GameRequestHandler* g = new GameRequestHandler(this->m_user.getUsername(), this->m_user.getSocket(), this->m_gameManager, this->m_handlerFactory, this->m_game);
	return { JsonResponsePacketSerializer::serializeResponse(m_game.getGameStatus()), g };
}

RequestResult GameRequestHandler::bankRequest() const
{
	bool temp = m_game.tryCardBank();
	LoginResponse resp = { 200 };
	if (temp)
	{
		resp.status = 100;
	}
	return { JsonResponsePacketSerializer::serializeResponse(resp),nullptr };

}

RequestResult GameRequestHandler::playCardRequest(const RequestInfo request) const {
	Card ret;
	std::string temp_str = JsonRequestPacketDeserializer::deserializePlaceCard(request.buffer);
	ret.color = m_game.getColor(temp_str);
	ret.what = m_game.getWhat(temp_str);
	bool temp = m_game.tryPlacement(ret);
	LoginResponse resp = { 200 };
	if (temp)
	{
		resp.status = 100;
	}
	return { JsonResponsePacketSerializer::serializeResponse(resp),nullptr };
}


