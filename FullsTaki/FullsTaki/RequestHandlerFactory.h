#pragma once
#include "incs.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h";
#include "RoomRequestHandler.h";
#include "RoomMemberRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class RequestHandlerFactory
{
public:

	RequestHandlerFactory(IDatabase* database);

	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();

	MenuRequestHandler* createMenuRequestHandler(LoggedUser* user);

	MenuRequestHandler* createMenuRequestHandler(const string username, const SOCKET socket);

	RoomAdminRequestHandler* createRoomAdminRequestHandler(Room* room, LoggedUser* user);

	RoomAdminRequestHandler* createRoomAdminRequestHandler(const string username, const SOCKET socket, const int roomId, RoomManager* temp);

	RoomAdminRequestHandler* createRoomAdminRequestHandler(const string username, const SOCKET socket, const int roomId);

	RoomRequestHandler* createRoomRequestHandler(Room* room, LoggedUser* user);

	RoomMemberRequestHandler* createRoomMemberRequestHandler(const string username, const SOCKET socket, const int roomId);

	LoginManager& getLoginManager();

	IDatabase* getDataBase();
	
private:
	RoomManager m_roomManager;
	LoginManager m_loginManager;
	IDatabase* m_database;
};