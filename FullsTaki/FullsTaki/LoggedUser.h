#pragma once
#include "incs.h"

class LoggedUser
{
public:
	LoggedUser(const std::string username, const SOCKET socket);
	~LoggedUser() = default;
	string getUsername() const;
	SOCKET getSocket() const;
	void setSocket(SOCKET sock);
	bool operator==(const LoggedUser user) const;
	void operator=(const LoggedUser user);
	void operator=(const LoggedUser* user);
private:
	string m_username;
	SOCKET m_socket;
};