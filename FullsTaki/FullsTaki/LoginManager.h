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

	void signup(const string username, const string password, const string email);

	void login(const string username, const string password);

	void logout(const string username);


private:
	vector<LoggedUser> m_loggedUsers;
	IDatabase* m_database;
};