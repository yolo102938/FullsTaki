#pragma once
#include "IDatabase.h"


#define DB_FILE_NAME "TakiDatabase.db"

using std::string;
using std::cout;
using std::endl;

#define USERS_CALLBACK 0
#define PASSWORDS_CALLBACK 1

class SqliteDataBase : public IDatabase
{
public:
	virtual bool doesUserExist(const string username) override;
	virtual bool doesPasswordMatch(const string username, const string password) override;
	virtual void addNewUser(const string username, const string password, const string email) override;
	virtual bool open() override;
	virtual void close() override;
private:
	bool executeQuery(const string query);
	bool executeQueryWithCallback(const string query, const int callbackID, void* data);
	sqlite3* _db;
};