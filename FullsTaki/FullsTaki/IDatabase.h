#pragma once
#include <iostream>
#include <string>
#include <list>
#include <io.h>
#include "sqlite3.h"

using std::string;

class IDatabase
{
public:

	virtual bool doesUserExist(const string username) = 0;

	virtual bool doesPasswordMatch(const string username, const std::string password) = 0;

	virtual void addNewUser(const string username, const string password, const string email) = 0;

	virtual bool open() = 0;

	virtual void close() = 0;
};