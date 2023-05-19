#include "Room.h"

void Room::addUser(LoggedUser user)
{
    m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
    for(auto iter = m_users.begin(); iter != m_users.end();){
        if (iter->getUsername() == user.getUsername())
        {
            iter = m_users.erase(iter);
        }
    }

}

std::vector<std::string> Room::getAllUsers()
{
    std::vector<std::string> ret;
    for (const auto& user : m_users)
    {
        ret.push_back(user.getUsername());  
    }

    return ret;
}
