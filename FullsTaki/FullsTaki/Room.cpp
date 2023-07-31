#include "Room.h"

Room::Room(const Room& room)
{
	try
	{
		this->m_metadata = room.m_metadata;
		this->m_users = room.m_users;
	}
	catch (...)
	{
	}
}

void Room::addUser(const LoggedUser user)
{
	this->mtx.lock();

	if (this->m_users.size() >= this->m_metadata.maxPlayers)
	{
		this->mtx.unlock();
		throw std::exception("ERROR: Room is full");
	}

	else if (std::find(this->m_users.begin(), this->m_users.end(), user) != this->m_users.end())
	{
		mtx.unlock();
		throw std::exception("ERROR: User already exists in this room");
	}

	else
	{
		m_users.push_back(user);
		mtx.unlock();
	}
}


void Room::removeUser(const LoggedUser user)
{
	mtx.lock();

	bool exist = false;
	auto it = m_users.begin();

	while (it != m_users.end() && !exist)
	{
		if (it->getUsername() == user.getUsername())
			exist = true;
		else
			it++;
	}

	if (exist)
	{
		m_users.erase(it);
		mtx.unlock();
	}

	else
	{
		mtx.unlock();
		throw std::exception("ERROR: User doesn't exist in this room");
	}
}


vector<string> Room::getAllUsers() const
{
	mtx.lock();

	std::vector<std::string> userNames = {};
	for (auto const& user : m_users)
	{
		userNames.push_back(user.getUsername());
	}

	mtx.unlock();
	return userNames;
}
