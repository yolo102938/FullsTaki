#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <random>
typedef struct Card
{
    std::string color;
    std::string what;
    bool operator==(const Card& other) const
    {
        return color == other.color && what == other.what;
    }
}Card;

typedef struct Player {
    std::string name;
    std::vector<Card> cards;
} Player;

class  GameData {
public:
    std::vector<Player> players;
    std::vector<Card> cards;
    std::string turn;
    Card placed_card;
    int status = 100;
private:
    int L = 9;
};

void generateCards(std::vector<Card>& av_Cards);

void shuffleCards(std::vector<Card>& cards);
