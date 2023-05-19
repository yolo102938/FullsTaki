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
} ErrorResponse;


class Room
{
public:

	void addUser(LoggedUser);
	void removeUser(LoggedUser);
	vector<string> getAllUsers();
	RoomData getRoomData() { return m_metadata; };
	vector<LoggedUser> getUsers() { return m_users; };

private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};
