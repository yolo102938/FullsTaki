#pragma once
#include "incs.h"

class LoggedUser
{
public:
	LoggedUser(string username);
	string getUsername() const;

private:
	string m_username;
};