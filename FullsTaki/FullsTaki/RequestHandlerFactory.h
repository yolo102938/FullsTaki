#pragma once
#include "incs.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h";
//#include "RoomRequestHandler.h";
class LoginRequestHandler;
class MenuRequestHandler;
class RequestHandlerFactory
{
public:

	RequestHandlerFactory(IDatabase* database);

	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();

	MenuRequestHandler* createMenuRequestHandler(LoggedUser* user);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(Room* room, LoggedUser* user);

	LoginManager& getLoginManager();
	

	IDatabase* getDataBase();
	
private:
	RoomManager m_roomManager;
	LoginManager m_loginManager;
	IDatabase* m_database;
};