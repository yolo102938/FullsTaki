#pragma once
#include "Game.h"
#include "IDatabase.h"
#include "Room.h"
#include <map>
#include <time.h>
#include <mutex>

using std::list;
using std::mutex;

class GameManager
{
public:
	//constructor
	GameManager(IDatabase* db);
	//default destructor
	~GameManager() = default;
	//function creates a game for the given room reference.
	Game& createGame(LoggedUser* user, const Room& room);
	//function deletes a game by a given Game reference.
	void deleteGame(const Game& game);
	//function returns a reference for the Game object matching the given id.
	Game& getGame(const int ID) const;

private:
	IDatabase* m_database;
	vector<Game*> m_games;
	mutable mutex games_mtx;
};