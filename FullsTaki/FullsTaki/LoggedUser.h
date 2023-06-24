#pragma once
#include "incs.h"

class LoggedUser
{
public:
	LoggedUser(const std::string username, const SOCKET socket);
	~LoggedUser() = default;
	string getUsername() const;
	SOCKET getSocket() const;
	bool operator==(const LoggedUser user) const;
	void operator=(const LoggedUser user);
	void operator=(const LoggedUser* user);
private:
	string m_username;
	const SOCKET m_socket;
};