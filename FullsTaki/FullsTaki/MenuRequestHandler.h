#pragma once
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class MenuRequestHandler : public IRequestHandler {
    public:
        virtual bool isRequestRelevant(const RequestInfo request) const override;
        virtual RequestResult handleRequest(const RequestInfo request) const override;
        //constructor                                                                                                                                                                                                                                           /* m_statisticsManager(statsManager),*/
        MenuRequestHandler(LoggedUser* user,RoomManager* roomManager,RoomManager* statsManager,RequestHandlerFactory* handlerFactory,LoginManager* loginManager):
          IRequestHandler(),m_handlerFactory(handlerFactory),m_user(user),m_roomManager(roomManager),m_loginManager(loginManager){}
    private:
        RequestResult signout(RequestInfo request) const;
        RequestResult getRooms(RequestInfo request) const;
        RequestResult getPlayersInRoom(RequestInfo request) const;
        RequestResult getPersonalStats(RequestInfo request) const;
        RequestResult getHighScore(RequestInfo request) const;
        RequestResult joinRoom(RequestInfo request) const;
        RequestResult createRoom(RequestInfo request) const;
        LoggedUser* m_user;
        RoomManager* m_roomManager;
        LoginManager* m_loginManager; //hpw am i supposed to logout without this
        RequestHandlerFactory* m_handlerFactory;
        //StatisticsManager* m_statisticsManager;


};