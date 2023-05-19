#pragma once
#pragma once
#include "incs.h"
#include "IDatabase.h"
#include "LoggedUser.h"
#include "Room.h"

class RoomManager
{
public: 

	void createRoom(LoggedUser, RoomData);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	vector<RoomData> getRooms();
	Room& getRoom(int ID);

private:
	map<roomID, Room> m_rooms;
};