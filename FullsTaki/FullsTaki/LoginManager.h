#pragma once
#include "incs.h"
#include "IDatabase.h"




class LoginManager
{
public:

	void login(const string username, const string password, const SOCKET socket);

	void signup(const string username, const string password, const string email);

	void logout(const string username);

private:

	IDatabase* m_database;
};