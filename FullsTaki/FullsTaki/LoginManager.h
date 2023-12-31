#pragma once
#include "incs.h"
#include "IDatabase.h"
#include "LoggedUser.h"


class LoginManager
{
public:

	static LoginManager& staticInstance(IDatabase* db)
	{
		static LoginManager instance(db);
		return instance;
	}

	LoginManager(IDatabase* database);

	~LoginManager();

	void signup(const string username, const string password, const string email, SOCKET sock);

	void login(const string username, const string password, SOCKET sock);

	void logout(const string username);
	vector<LoggedUser> m_loggedUsers;

private:
	
	IDatabase* m_database;
};