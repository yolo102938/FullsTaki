#include "SqliteDatabase.h"

static int usersCallback(void* _data, int argc, char** argv, char** azColName)
{
	auto& usersList = *static_cast<std::list<string>*>(_data);
	string username = "";

	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "username")
			username = argv[i];
	}

	usersList.push_back(username);
	return 0;
}


static int passwordsCallback(void* _data, int argc, char** argv, char** azColName)
{
	auto& password = *static_cast<string*>(_data);

	if (string(azColName[0]) == "password")
		password = argv[0];

	return 0;
}

bool SqliteDataBase::doesUserExist(const string username)
{
	std::list<string> users;
	users.clear();

	string query = "SELECT USERNAME FROM USERS WHERE USERNAME = '" + username + "';";
	executeQueryWithCallback(query, usersCallback, &users);

	return !users.empty();
}

bool SqliteDataBase::doesPasswordMatch(const string username, const string password)
{
	string userPassword;
	
	string query = "SELECT PASSWORD FROM USERS WHERE USERNAME = '" + username + "';";
	executeQueryWithCallback(query, PASSWORDS_CALLBACK, &userPassword);
	std::cout << userPassword + " real->" + password;
	return userPassword == password;
}

void SqliteDataBase::addNewUser(const string username, const string password, const string email)
{
	string query = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES ('" + username + "', '" + password + "', '" + email + "');";
	executeQuery(query);
}

/*
Function opens/creates the database file for the program.
Input: none.
Output: bool(true/false --> success/failure)
*/
bool SqliteDataBase::open()
{
	int doesFileExist = _access(DB_FILE_NAME, 0); //checking if a database file with the stated name exists (returns -1 if not)
	int res = sqlite3_open(DB_FILE_NAME, &this->_db); //creating/opening the database.

	if (res != SQLITE_OK) //if the creation/opening faild, setting the database pointer to null and returning false.
	{
		this->_db = nullptr;
		return false;
	}

	if (doesFileExist == -1) //if the database file was created only now, setting the content tables.
	{
		return !(!executeQuery("CREATE TABLE IF NOT EXISTS USERS (USERNAME TEXT PRIMARY KEY AUTOINCREMENT NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);"));
	}
	return true; //if everything went well, and the database was created and set-up or opend, returning true.
}

/*
Function closes the database access, and reset's the database pointer to nullptr.
Input: none.
Output: none.
*/
void SqliteDataBase::close()
{
	sqlite3_close(this->_db); //closing the connection to the database.
	this->_db = nullptr; //setting the class's database pointer to nullptr.
}

/*
Function executes a given string query on the database, and returns the execution result (faild -> false | succeeded -> true)
Input: const string query
Output: bool res (result)
*/
bool SqliteDataBase::executeQuery(const string query)
{
	char* errMessage = nullptr; //setting a variable to contain the error message (in case an error occurred).
	//executing the query, and setting res to true/false based on success/failure.
	bool res = (sqlite3_exec(this->_db, query.c_str(), nullptr, nullptr, &errMessage) == SQLITE_OK);

	//if errMessage contains data, an error occurred. printing the error to the user.
	if (errMessage != nullptr)
	{
		cout << "ERROR: " << errMessage << endl;
	}

	//returning the result.
	return res;
}

/*
Function executes a given string query on the database, using a callback function of a given ID, and returns the execution result (faild -> false | succeeded -> true)
Input: const string query, const int callbackID, void* data (default --> nullptr)
Output: bool res (result)
*/
bool SqliteDataBase::executeQueryWithCallback(const string query, const int callbackID, void* data)
{
	char* errMessage = nullptr; //setting a variable to contain the error message (in case an error occurred).
	bool res = false; //setting res (the result variable).

	switch (callbackID)
	{
	case 0: //execute the query with users callback
		data = &this->_db;
		res = sqlite3_exec(this->_db, query.c_str(), usersCallback, data, &errMessage) == SQLITE_OK; //executing the query, and setting res to true/false based on success/failure.
		break;
	case 1: //execute the query with passwords callback
		data = &this->_db;
		res = sqlite3_exec(this->_db, query.c_str(), passwordsCallback, data, &errMessage) == SQLITE_OK; //executing the query, and setting res to true/false based on success/failure.
		break;
	}

	//if errMessage contains data, an error occurred. printing the error to the user.
	if (errMessage != nullptr)
	{
		cout << "ERROR: " << errMessage << endl;
	}

	//returning the result.
	return res;
}