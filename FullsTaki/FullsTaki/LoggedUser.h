#pragma once
#include "incs.h"

class LoggedUser
{
public:
	LoggedUser(string username);
	LoggedUser(const std::string username, const SOCKET socket);
	~LoggedUser() = default;
	string getUsername() const;
	SOCKET getSocket() const;
	bool operator==(const LoggedUser user) const;
private:
	string m_username;
	SOCKET m_socket;
};