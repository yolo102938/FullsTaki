#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_database(database), m_roomManager(), m_loginManager(database), m_gameManager(database)
{}

RequestHandlerFactory::~RequestHandlerFactory()
{
    delete m_database;
    m_database = nullptr;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser* user)
{
    return new MenuRequestHandler(user, &m_roomManager, nullptr, this);
}
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const string username, const SOCKET socket)
{
    return new MenuRequestHandler(username, socket, this->m_roomManager, *this);
}
LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->m_loginManager;
}
 
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(Room* room, LoggedUser* user)
{
     return new RoomAdminRequestHandler(room, user, m_roomManager, this);
}
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const string username, const SOCKET socket, const int roomId)
{
    return new RoomAdminRequestHandler(username, socket, this->m_roomManager, *this, roomId);
}
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const string username, const SOCKET socket, const int roomId, RoomManager* temp)
{
    m_roomManager = *temp;
    return new RoomAdminRequestHandler(username, socket, this->m_roomManager, *this, roomId);
}
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(const string username, const SOCKET socket, const int roomId)
{
    return new RoomMemberRequestHandler(username, socket, this->m_roomManager, *this, roomId);
}

IDatabase* RequestHandlerFactory::getDataBase()
{
    return this->m_database;
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(const string username, const SOCKET socket, const int roomId, RoomManager* temp)
{
    m_roomManager = *temp;
    return new RoomMemberRequestHandler(username, socket, this->m_roomManager, *this, roomId);
}

GameManager& RequestHandlerFactory::getGameManager()
{
    return this->m_gameManager;
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(const string username, const SOCKET socket, Game& game)
{
    return new GameRequestHandler(username, socket, this->m_gameManager, *this, game);
}
