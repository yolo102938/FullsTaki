#pragma once
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "ServerData.h"
class RequestHandlerFactory;
class MenuRequestHandler : public IRequestHandler {
    public:
        virtual bool isRequestRelevant(const RequestInfo request) const override;
        virtual RequestResult handleRequest(const RequestInfo request) const override;
        //constructor                                                                                                                                                                                                                                           /* m_statisticsManager(statsManager),*/
        MenuRequestHandler(LoggedUser* user,RoomManager* roomManager,RoomManager* statsManager,RequestHandlerFactory* handlerFactory):
          IRequestHandler(),m_handlerFactory(handlerFactory),m_user(user),m_roomManager(roomManager){}
        MenuRequestHandler(const string username, const SOCKET socket, RoomManager& roomManager,RequestHandlerFactory& factory)
        {
            m_user = new LoggedUser(username, socket);
            m_roomManager = new RoomManager(roomManager);
            m_handlerFactory = &factory;
        }
    private:
        RequestResult logout(const RequestInfo request) const;
        RequestResult getRooms(RequestInfo request) const;
        RequestResult getPlayersInRoom(RequestInfo request) const;
        RequestResult getPersonalStats(RequestInfo request) const;
        RequestResult getHighScore(RequestInfo request) const;
        RequestResult joinRoom(RequestInfo request) const;
        RequestResult createRoom(RequestInfo request) const;
        mutable LoggedUser* m_user;
        mutable RoomManager* m_roomManager;
        mutable RequestHandlerFactory* m_handlerFactory;
        //StatisticsManager* m_statisticsManager;


};