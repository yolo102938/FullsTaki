#pragma once
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
class MenuRequestHandler {
    public:
        bool isRequestRelevant(RequestInfo request);
        RequestResult handleRequest(RequestInfo request);
        //constructor
        MenuRequestHandler(LoggedUser* user,RoomManager* roomManager,RoomManager* statsManager,RequestHandlerFactory* handlerFactory) : m_user(user), m_roomManager(roomManager),/* m_statisticsManager(statsManager),*/ m_handlerFactory(handlerFactory) {}
    private:
        RequestResult signout(RequestInfo request);
        RequestResult getRooms(RequestInfo request);
        RequestResult getPlayersInRoom(RequestInfo request);
        RequestResult getPersonalStats(RequestInfo request);
        RequestResult getHighScore(RequestInfo request);
        RequestResult joinRoom(RequestInfo request);
        RequestResult createRoom(RequestInfo request);
        LoggedUser* m_user;
        RoomManager* m_roomManager;
        RequestHandlerFactory* m_handlerFactory;
        //StatisticsManager* m_statisticsManager;


};