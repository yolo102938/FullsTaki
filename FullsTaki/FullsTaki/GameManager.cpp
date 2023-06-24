#include "GameManager.h"

GameManager::GameManager(IDatabase* db)
{
	this->m_database = db;
}


Game& GameManager::createGame(LoggedUser* user, const Room& room)
{
	vector<LoggedUser> players = room.m_users;

	Game* new_game = new Game(user, players, room.m_metadata.id);

	room.m_metadata.isActive = true;

	this->games_mtx.lock();
	this->m_games.push_back(new_game);
	this->games_mtx.unlock();

	return (*new_game);
}


void GameManager::deleteGame(const Game& game)
{
	this->games_mtx.lock();
	for (vector<Game*>::iterator curr_game = m_games.begin(); curr_game != m_games.end(); curr_game++)
	{
		if ((*curr_game)->gameId == game.gameId)
		{
			delete* curr_game;
			this->m_games.erase(curr_game);
			this->games_mtx.unlock();
			return;
		}
	}

	this->games_mtx.unlock();
}


Game& GameManager::getGame(const int id) const
{
	this->games_mtx.lock();
	for (Game* game : this->m_games)
	{
		if (game->gameId == id)
		{
			this->games_mtx.unlock();
			return *game;
		}
	}

	this->games_mtx.unlock();
}

