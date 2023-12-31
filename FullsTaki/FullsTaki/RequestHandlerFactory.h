#pragma once
#include "incs.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h";
#include "RoomMemberRequestHandler.h"
#include "GameManager.h"
#include "GameRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:

	RequestHandlerFactory(IDatabase* database);

	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();

	MenuRequestHandler* createMenuRequestHandler(LoggedUser* user);

	MenuRequestHandler* createMenuRequestHandler(const string username, const SOCKET socket);

	RoomMemberRequestHandler* createRoomMemberRequestHandler(const string username, const SOCKET socket, const int roomId, RoomManager* temp);

	RoomAdminRequestHandler* createRoomAdminRequestHandler(Room* room, LoggedUser* user);

	RoomAdminRequestHandler* createRoomAdminRequestHandler(const string username, const SOCKET socket, const int roomId, RoomManager* temp);

	RoomAdminRequestHandler* createRoomAdminRequestHandler(const string username, const SOCKET socket, const int roomId);

	RoomMemberRequestHandler* createRoomMemberRequestHandler(const string username, const SOCKET socket, const int roomId);

	GameRequestHandler* createGameRequestHandler(const string username, const SOCKET socket, Game& game);

	GameManager& getGameManager();

	LoginManager& getLoginManager();

	IDatabase* getDataBase();
	
private:
	GameManager m_gameManager;
	mutable RoomManager m_roomManager;
	LoginManager m_loginManager;
	IDatabase* m_database;
};