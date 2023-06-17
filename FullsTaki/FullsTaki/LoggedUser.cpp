#include "LoggedUser.h"

LoggedUser::LoggedUser(string username)
{
	this->m_username = username;
}
LoggedUser::LoggedUser(const std::string username, const SOCKET socket)
{
	this->m_username = username;
	this->m_socket = socket;
}
string LoggedUser::getUsername() const
{
	return this->m_username;
}
SOCKET LoggedUser::getSocket() const
{
	return this->m_socket;
}
bool LoggedUser::operator==(const LoggedUser user) const
{
	return this->m_username == user.m_username;
}