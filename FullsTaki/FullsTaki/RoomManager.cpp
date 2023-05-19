#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, RoomData data)
{
    m_rooms[data.id] = Room(data, user);;
}

void RoomManager::deleteRoom(int ID)
{
    m_rooms.erase(ID);
}

unsigned int RoomManager::getRoomState(int ID)
{
    return m_rooms[ID].getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
    std::vector<RoomData> ret;
    for (auto room : m_rooms)
    {
        ret.push_back(room.second.getRoomData());
    }

    return ret;
}

Room& RoomManager::getRoom(int ID)
{
    return m_rooms[ID];
}
