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
	bool doesUserExist(const string username) override;
	bool doesPasswordMatch(const string username, const string password) override;
	void addNewUser(const string username, const string password, const string email) override;
	bool open() override;
	void close() override;
private:
	bool executeQuery(const string query);
	bool executeQueryWithCallback(const string query, const int callbackID, void* data);
	sqlite3* _db;
};