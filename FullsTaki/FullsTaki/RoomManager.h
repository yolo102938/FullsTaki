#pragma once
#pragma once
#include "incs.h"
#include "IDatabase.h"
#include "LoggedUser.h"
#include "Room.h"

class RoomManager
{
public: 

	void createRoom(const LoggedUser user, RoomData& data);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	vector<RoomData> getRooms();
	Room& getRoom(int ID);
	bool hasRoom(const int ID) const;

private:
	std::map<int, Room> m_rooms;
	int prevRoomId;
};