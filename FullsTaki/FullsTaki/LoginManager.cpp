#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* database) : m_database(database)
{

}

LoginManager::~LoginManager()
{
	this->m_loggedUsers.clear();
}

void LoginManager::signup(const string username, const string password, const string email)
{
	if (this->m_database->doesUserExist(username))
	{
		throw exception("SIGNUP ERROR: A user with this username already exists");
	}
	else
	{
		this->m_database->addNewUser(username, password, email);
		this->m_loggedUsers.push_back(LoggedUser(username));
	}
}


void LoginManager::login(const string username, const string password)
{
	for (auto& user : this->m_loggedUsers)
	{
		if (username == user.getUsername())
		{
			throw exception("LOGIN ERROR: User is already logged in");
		}
	}

	if (this->m_database->doesPasswordMatch(username, password))
	{
		this->m_loggedUsers.push_back(LoggedUser(username));
	}
	else
	{
		throw exception("LOGIN ERROR: Invalid password or username");
	}
}

void LoginManager::logout(string username)
{
	for (auto it = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); it++)
	{
		if (it->getUsername() == username)
		{
			this->m_loggedUsers.erase(it);
			return;
		}
	}
	throw exception("LOGOUT ERROR: User isn't logged in");
}