#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->m_loginManager;
}

IDatabase* RequestHandlerFactory::getDataBase()
{
    return this->m_database;
}