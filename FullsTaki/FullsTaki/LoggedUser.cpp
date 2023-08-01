#include "LoggedUser.h"

LoggedUser::LoggedUser(const std::string username, const SOCKET socket) : m_username(username), m_socket(socket)
{}

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

void LoggedUser::operator=(const LoggedUser user)
{
	this->m_username = user.m_username;
}

void LoggedUser::operator=(const LoggedUser* user)
{
	this->m_username = user->m_username;
}

void LoggedUser::setSocket(SOCKET sock)
{
	this->m_socket = sock;
}