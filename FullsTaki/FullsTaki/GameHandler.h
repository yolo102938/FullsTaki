#pragma once
#include "incs.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "ServerData.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <random>
#include <mutex>
#include <string>
class RequestHandlerFactory;



std::vector<Card> generateCards(std::vector<Card>& av_Cards) {
    std::vector<std::string> colors = { "Red", "Green", "Blue", "Yellow" };
    std::vector<std::string> symbols = { "Skip", "Draw" };
    for (const auto& color : colors) {
        for (int number = 0; number < 10; ++number) {
            Card card = {color , std::to_string(number)};
            av_Cards.push_back(card);
            av_Cards.push_back(card);
        }
    }
    for (const auto& color : colors) {
        for (const auto& symbol : symbols) {
            Card card = { color , symbol };
            av_Cards.push_back(card);
            av_Cards.push_back(card);
            av_Cards.push_back(card);
            av_Cards.push_back(card);
        }
    }
}


void shuffleCards(std::vector<Card>& cards) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

class Game {
public:
    Game() 
    {
        generateCards(av_Cards);
        shuffleCards(av_Cards);
        current_player = 0;
        current_card = { "None","None" };
        last_card = { "None","None" };
    }
    bool tryPlacement(Card card);
    bool tryCardBank();
    GameData getGameState();
    std::string getWhat(std::string card) {
        std::string full = card;
        std::string colors[] = { "Red", "Green", "Blue", "Yellow" };
        for (const std::string& color : colors) {
            size_t pos = full.find(color);
            while (pos != std::string::npos) {
                full.replace(pos, color.length(), "");
                pos = full.find(color);
            }
        }
        return full;
    }
    std::string getColor(std::string card) {
        std::string full = card;
        std::string colors[] = { "Red", "Green", "Blue", "Yellow" };
        for (const std::string& color : colors) {
            size_t pos = full.find(color);
            if (pos != std::string::npos) {
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
class GameHandler : public IRequestHandler {
public:
    GameHandler(LoggedUser* user, RequestHandlerFactory* handlerFactory);

    virtual bool isRequestRelevant(const RequestInfo request) const override;
    virtual RequestResult handleRequest(const RequestInfo request) const override;
    

    RequestResult gameState() const;
    RequestResult bankRequest() const;
    RequestResult playCardRequest(const RequestInfo request) const;

private:




    Game* m_game;
    LoggedUser* m_user;
    RequestHandlerFactory* m_handlerFactory;
};




