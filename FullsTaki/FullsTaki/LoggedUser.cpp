#include "LoggedUser.h"

LoggedUser::LoggedUser(string username)
{
	this->m_username = username;
}

string LoggedUser::getUsername() const
{
	return this->m_username;
}