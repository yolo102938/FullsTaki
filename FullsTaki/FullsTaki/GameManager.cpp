#include "GameManager.h"

GameManager::GameManager(IDatabase* db)
{
	this->m_database = db;
}


Game& GameManager::createGame(const Room& room)
{
	vector<LoggedUser> players = room.m_users;

	Game* new_game = new Game(players, room.m_metadata.id);

	this->games_mtx.lock();
	this->m_games.push_back(new_game);
	this->games_mtx.unlock();

	return (*new_game);
}
Game& GameManager::getGame(const Room& room)
{
	vector<LoggedUser> players = room.m_users;

	Game* new_game = nullptr;
	for (auto g : this->m_games) {

		if (g->m_players[0] == room.getAllUsers()[0]) {
			new_game = g;
		}
	}
	return (*new_game);
}

void GameManager::deleteGame(const Game& game)
{
	this->games_mtx.lock();
	for (vector<Game*>::iterator curr_game = m_games.begin(); curr_game != m_games.end(); curr_game++)
	{
		if ((*curr_game)->getGameId() == game.getGameId())
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
		if (game->getGameId() == id)
		{
			this->games_mtx.unlock();
			return *game;
		}
	}

	this->games_mtx.unlock();
}

