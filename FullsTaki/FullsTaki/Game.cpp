#include "Game.h"

Game::Game(const vector<LoggedUser> users, const int gameId)
{
	this->players_mtx.lock();
	for (LoggedUser user : users)
	{
		this->m_players.push_back(user);
	}
	this->players_mtx.unlock();

	this->game_id = gameId;
	this->usersInGame = 0;
}

Game::Game(const Game& game)
{
	this->m_players = game.m_players;
	this->game_id = game.game_id;
	this->usersInGame = game.usersInGame;
}

void Game::operator=(const Game& game)
{
	*this = Game(game);
}

void Game::playCard(const LoggedUser user, const unsigned int answer)
{
	this->players_mtx.lock();

	this->players_mtx.unlock();
}


int Game::getGameId() const
{
	return this->game_id;
}