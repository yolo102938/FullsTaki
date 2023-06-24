#include "Game.h"

bool CheckInPlayers(vector<Player> players, string name);


Game::Game(int gameId)
{
    mutexGame.lock();
    generateCards(av_Cards);
    shuffleCards(av_Cards);
    current_player = 0;
    current_card = { "None","None" };
    last_card = { "None","None" };
    this->gameId = gameId;
    start = 0;
    mutexGame.unlock();
}
Game::Game(Game& game, LoggedUser* user)
{

}
Game::Game(LoggedUser* curr, vector<LoggedUser> users, int gameId)
{
    mutexGame.lock();
    generateCards(av_Cards);
    shuffleCards(av_Cards);
    current_player = 0;
    current_card = { "None","None" };
    last_card = { "None","None" };
    m_user = curr;
    this->gameId = gameId;
    start = 0;
    for (int i = 0; i < users.size(); i++)
    {
        vector<Card> cv;
        this->players.push_back(Player{ users[i].getUsername(), cv });
    }
    mutexGame.unlock();
}

//function will check if its allowed to place a card in the middle. if it is allowed, it will place it and make all of the changes.
//then it will return true or false if it did it or not.
bool Game::tryPlacement(Card card)
{
    mutexGame.lock();
    if (players[current_player].name == m_user->getUsername() && current_card.what != "Draw") {
        if (current_card.color == "None" && last_card.color == "None") {
            current_card = card;
            last_card = card;
            players[current_player].cards.erase(std::remove(players[current_player].cards.begin(), players[current_player].cards.end(), card), players[current_player].cards.end());
            if (card.what == "Skip") {
                current_player = (current_player + 2) % players.size();
                current_card = { "None","None" };
                last_card = card;
            }
            else {
                current_player = (current_player + 1) % players.size();
            }
            av_Cards.push_back(card);
            shuffleCards(av_Cards);
            mutexGame.unlock();
            return true;
        }
        else if (current_card.what != "None" && current_card.what == card.what || current_card.color == card.color) {
            current_card = card;
            last_card = card;
            for (auto it = players[current_player].cards.begin(); it != players[current_player].cards.end(); ++it) {
                if (it->color == card.color && it->what == card.what) {
                    players[current_player].cards.erase(it);
                    break;
                }
            }
            if (card.what == "Skip") {
                current_player = (current_player + 2) % players.size();
                current_card = { "None","None" };
                last_card = card;
            }
            else {
                current_player = (current_player + 1) % players.size();
            }
            av_Cards.push_back(card);
            shuffleCards(av_Cards);
            mutexGame.unlock();
            return true;
        }
        else if (last_card.what != "None" && last_card.what == card.what || last_card.color == card.color) {
            current_card = card;
            last_card = card;
            for (auto it = players[current_player].cards.begin(); it != players[current_player].cards.end(); ++it) {
                if (it->color == card.color && it->what == card.what) {
                    players[current_player].cards.erase(it);
                    break;
                }
            }
            if (card.what == "Skip") {
                current_player = (current_player + 2) % players.size();
                current_card = { "None","None" };
                last_card = card;
            }
            else {
                current_player = (current_player + 1) % players.size();
            }
            av_Cards.push_back(card);
            shuffleCards(av_Cards);
            mutexGame.unlock();
            return true;
        }
    }
    mutexGame.unlock();
    return false;
}


bool Game::tryCardBank()
{
    mutexGame.lock();
    if (players[current_player].name == m_user->getUsername()) {
        if (av_Cards.empty()) {
            generateCards(av_Cards);
            shuffleCards(av_Cards);
        }
        Card card = av_Cards.back();
        av_Cards.pop_back();
        players[current_player].cards.push_back(card);

        if (current_card.what == "Draw") {
            card = av_Cards.back();
            av_Cards.pop_back();
            players[current_player].cards.push_back(card);
        }
        last_card = current_card;
        current_card = { "None","None" };
        current_player = (current_player + 1) % players.size();
        mutexGame.unlock();
        return(true);
    }
    else {
        mutexGame.unlock();
        return(false);
    }
}

GameData Game::getGameStatus()
{
    mutexGame.lock();
    std::vector<Player*> other_players;
    Player* tempPlayer = new Player;
    std::string name_temp;
    if (players.size() > 0)
    {
        name_temp = players[current_player % 2].name;
    }
    else
    {
        name_temp = "";
    }

    //debug
    std::cout << "\nGAME STATUS FUNC | Names: ";
    for (Player p : players)
    {
         std::cout << p.name << " , ";
    }
    std::cout << "Count: " << players.size() << "\CurrentPlayerNum: " << current_player << std::endl;

    std::vector<Card> crds = std::vector<Card>();
    bool present = CheckInPlayers(players, name_temp); //is he in the player list already

    for (auto& player : players)
    {
        if (player.name == m_user->getUsername())
        {
            tempPlayer = &player;
            name_temp = "You";
            crds = player.cards;
        }
        else
        {
            other_players.push_back(&player);
        }
    }

    if (!present)
    {
        std::vector<Card>* first_cards = new std::vector<Card>();
        for (int i = 0; i < 7; i++)
        {
            Card temp = av_Cards.back();
            first_cards->push_back({ temp.color,temp.what });
            av_Cards.pop_back();
        }
        players.push_back({ m_user->getUsername(),*first_cards });
    }

    else if ((tempPlayer->cards.size() == 0) && (av_Cards.size() + other_players[0]->cards.size()) == 112)
    {
        std::vector<Card>* first_cards = new std::vector<Card>();
        for (int i = 0; i < 7; i++)
        {
            Card temp = av_Cards.back();
            tempPlayer->cards.push_back({ temp.color,temp.what });
            av_Cards.pop_back();
        }
    }

    if ((other_players[0]->cards.size() == 0) && (av_Cards.size() + tempPlayer->cards.size()) == 112)
    {
        std::vector<Card>* first_cards = new std::vector<Card>();
        for (int i = 0; i < 7; i++)
        {
            Card temp = av_Cards.back();
            other_players[0]->cards.push_back({ temp.color,temp.what });
            av_Cards.pop_back();
        }
    }

    GameData response_data;

    for (auto& player : other_players)
    {
        response_data.players.push_back(*player);
    }
    for (auto& card : tempPlayer->cards)
    {
        response_data.cards.push_back(card);
    }
    response_data.turn = name_temp;
    response_data.placed_card = current_card;
    current_player++;
    //std::cout << "\nCurrent Player: " << current_player << " --> " << players[current_player % 2].name;
    mutexGame.unlock();
    return response_data;

}

bool CheckInPlayers(vector<Player> players, string name)
{
    if (name == "")
    {
        return true;
    }
    for (Player player : players)
    {
        if (player.name == name)
        {
            return true;
        }
    }
    return false;
}
