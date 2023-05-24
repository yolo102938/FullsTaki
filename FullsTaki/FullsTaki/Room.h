#pragma once
#include "incs.h"
#include "IDatabase.h"
#include "LoggedUser.h"

typedef struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
} RoomData;


class Room
{
public:
	Room() { m_metadata = { 0, "temp", 0, 0 ,0 }; }
	Room(RoomData metadata, LoggedUser user) { m_metadata = metadata; m_users.push_back(user); }
	void addUser(LoggedUser);
	void removeUser(LoggedUser);
	vector<string> getAllUsers();
	RoomData getRoomData() { return m_metadata; };
	vector<LoggedUser> getUsers() { return m_users; };

private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};
