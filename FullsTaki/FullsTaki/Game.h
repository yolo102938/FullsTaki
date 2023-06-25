#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "LoggedUser.h"
#include <time.h>
#include <mutex>

using std::vector;
using std::map;
using std::string;
using std::multimap;
using std::mutex;

class Game
{
public:
    Game(int gameId);
    Game(Game& game, LoggedUser* user);
    Game(LoggedUser* curr, vector<LoggedUser> users, int gameId);

    GameData getGameStatus(LoggedUser* m_user);
    bool tryPlacement(Card card, LoggedUser* m_user);
    bool tryCardBank(LoggedUser* m_user);

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
    int gameId;
    std::vector<Player> players;
private:
    std::vector<Card> av_Cards;
    Card current_card;
    Card last_card;
    int current_player;
    int start;
    mutable mutex mutexGame;
};