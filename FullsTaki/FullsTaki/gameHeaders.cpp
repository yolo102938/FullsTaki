#include "gameHeaders.h"
void generateCards(std::vector<Card>& av_Cards)
{
    std::vector<std::string> colors = { "Red", "Green", "Blue", "Yellow" };
    std::vector<std::string> symbols = { "Skip", "Draw" };
    for (const auto& color : colors) {
        for (int number = 0; number < 10; ++number) {
            Card card = { color , std::to_string(number) };
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

void shuffleCards(std::vector<Card>& cards)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}