#pragma once
#include "incs.h"
#include "IDatabase.h"
#include "LoggedUser.h"
#include <mutex>

using std::mutex;
using std::string;

typedef struct RoomData
{
	unsigned int id = 0;
	string name;
	int maxPlayers = 4;
	unsigned int isActive = false;
	unsigned int timePerPlay = 10;
} RoomData;


class Room
{
public:
	Room() { m_metadata = { 0, "temp", 0,0 }; }
	Room(RoomData metadata, LoggedUser user) { m_metadata = metadata; m_users.push_back(user); }
	Room(RoomData data) {this->m_metadata = data;}
	Room(const Room& room);
	~Room() = default;
	void addUser(LoggedUser);
	void removeUser(LoggedUser);
	vector<string> getAllUsers() const;
	RoomData getRoomData() { return m_metadata; };
	vector<LoggedUser> getUsers() { return m_users; };
	vector<LoggedUser> m_users;
	mutable RoomData m_metadata;
private:
	mutable mutex mtx; // --> mutable - not const
};
