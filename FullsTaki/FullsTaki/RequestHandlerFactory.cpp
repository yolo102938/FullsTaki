#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) :
    m_database(database), m_loginManager(LoginManager(database))
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
    return new MenuRequestHandler(user, &m_roomManager, nullptr, this, &m_loginManager);
}
LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->m_loginManager;
}

IDatabase* RequestHandlerFactory::getDataBase()
{
    return this->m_database;
}