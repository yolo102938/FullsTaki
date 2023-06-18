#pragma once
#include "incs.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "ServerData.h"
#include <vector>
#include <map>

#include <iostream>

#include <mutex>
#include <string>


class RequestHandlerFactory;


class GameEngine
{
    public:
        GameEngine();


        GameData getGameStatus();
        bool tryPlacement(Card card);
        bool tryCardBank();
        
        std::string getWhat(std::string card)
        {
            std::string full = card;
            std::string colors[] = { "Red", "Green", "Blue", "Yellow" };
            for (const std::string& color : colors)
            {
                size_t pos = full.find(color);
                while (pos != std::string::npos)
                {
                    full.replace(pos, color.length(), "");
                    pos = full.find(color);
                }
            }
            return full;
        }
        std::string getColor(std::string card)
        {
            std::string full = card;
            std::string colors[] = { "Red", "Green", "Blue", "Yellow" };
            for (const std::string& color : colors)
            {
                size_t pos = full.find(color);
                if (pos != std::string::npos)
                {
                    return color;
                }
            }
            return "";
        }
    private:
        std::vector<Player> players;
        std::vector<Card> av_Cards;
        LoggedUser* m_user;
        Card current_card;
        Card last_card;
        int current_player;
};

class GameHandler : public IRequestHandler
{
    public:
        GameHandler(LoggedUser* user, RequestHandlerFactory* handlerFactory);
        ~GameHandler();
        virtual bool isRequestRelevant(const RequestInfo request) const override;
        virtual RequestResult handleRequest(const RequestInfo request) const override;
    
        
        RequestResult gameState() const;
        RequestResult bankRequest() const;
        RequestResult playCardRequest(const RequestInfo request) const;

    private:
        GameEngine* m_game;
        LoggedUser* m_user;
        RequestHandlerFactory* m_handlerFactory;
};




