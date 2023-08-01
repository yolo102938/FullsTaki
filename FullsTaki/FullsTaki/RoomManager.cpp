#include "RoomManager.h"

void RoomManager::createRoom(const LoggedUser user, RoomData& data)
{
    data.id = this->prevRoomId++;
    Room newRoom(data);
    newRoom.addUser(user);
    this->m_rooms.insert({ data.id, newRoom });
}

void RoomManager::deleteRoom(int ID)
{
    this->m_rooms.erase(this->m_rooms.find(ID));
}

unsigned int RoomManager::getRoomState(int ID)
{
    return this->m_rooms.find(ID)->second.getRoomData().isActive;
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

Room& RoomManager::getRoom(const int ID)
{
    for (auto& room : this->m_rooms)
    {
        if (room.first == ID)
        {
            return room.second;
        }
    }
}

bool RoomManager::hasRoom(const int ID) const
{
    return this->m_rooms.find(ID) != this->m_rooms.end();
}