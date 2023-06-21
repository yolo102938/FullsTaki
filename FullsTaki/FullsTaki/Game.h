#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "LoggedUser.h"
#include <time.h>
#include <mutex>

using std::vector;
using std::map;
using std::string;
using std::multimap;
using std::mutex;

class Game
{
public:
	//Constructors
	Game(const vector<LoggedUser> users, const int gameId);
	Game(const Game& game);

	//Operator overloading
	void operator=(const Game& game);

	//defult destructor for Game.
	~Game() = default;

	//function plays a card to the board and end's the given user's turn
	void playCard(const LoggedUser user, const unsigned int cardId);

	//function returns the game's id
	int getGameId() const;

	mutable vector<LoggedUser> m_players;

	mutable int usersInGame;

private:
	int game_id;
	mutable mutex players_mtx;
};