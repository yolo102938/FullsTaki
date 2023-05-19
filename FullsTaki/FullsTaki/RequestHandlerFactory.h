#pragma once
#include "incs.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"

class RequestHandlerFactory
{
public:

	RequestHandlerFactory(IDatabase* database);

	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();

	LoginManager& getLoginManager();

	IDatabase* getDataBase();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};