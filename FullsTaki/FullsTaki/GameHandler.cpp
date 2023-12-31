#include "GameHandler.h"


bool GameHandler::isRequestRelevant(const RequestInfo request) const
{
    return (request.id == GET_GAME_STATE) || (request.id == PREMISION_TO_PLACE_CARD|| request.id == CARD_BANK_PREMISION);
}


RequestResult GameHandler::handleRequest(const RequestInfo request) const
{
    try
    {
        if (request.id == GET_GAME_STATE) {
            return gameState();
        }
        else if (request.id == PREMISION_TO_PLACE_CARD) {
            return playCardRequest(request);
        }
        else if (request.id == CARD_BANK_PREMISION) {
            return bankRequest();
        }
    }

    catch (nlohmann::json::exception& e)
    {
        ErrorResponse res = { "ERROR: Request contains invalid json" };
        return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
    }

    catch (std::exception& e)
    {
        ErrorResponse res = { e.what() };
        return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
    }
}

RequestResult GameHandler::gameState() const
{
    GameHandler g = *this;
    return {JsonResponsePacketSerializer::serializeResponse(m_game->getGameState()), &g};
}

RequestResult GameHandler::bankRequest() const{
    bool temp = false;
    LoginResponse resp = { 200 };
    if (temp)
    {
        resp.status = 100;
    }
}
RequestResult GameHandler::playCardRequest(const RequestInfo request) const{
    Card ret;
    std::string temp_str = JsonRequestPacketDeserializer::deserializePlaceCard(request.buffer);
    ret.color = m_game->getColor(temp_str);
    ret.color = m_game->getWhat(temp_str);
    bool temp = m_game->tryPlacement(ret);
    LoginResponse resp = { 200 };
    if (temp)
    {
        resp.status = 100;
    }
}

GameHandler::GameHandler(LoggedUser* user, RequestHandlerFactory* handlerFactory) {
     m_user = user;
     m_handlerFactory = handlerFactory;
     m_game = new Game();
}





bool Game::tryCardBank() 
{
    if (players[current_player].name ==m_user->getUsername()) {
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
        return(true);
    }
    else {
        return(false);
    }
}

GameData Game::getGameState()
{
    std::vector<Player> other_players;
    std::string name_temp = players[current_player].name;
    std::vector<Card> crds;
    bool present = false; //is he in the player list already
    for (auto& player : players) {
        if (player.name == m_user->getUsername()) {
            if (player.name == players[current_player].name)
                present = true;
                name_temp = "You";
            crds = player.cards;
        }
        else 
        {
            other_players.push_back(player);
        }
    }
    if (!present) {
        std::vector<Card>* first_cards = new std::vector<Card>(8);
        for (int i = 0; i > 8; i++) {
            Card temp = av_Cards.back();
            first_cards->push_back({ temp.color,temp.what });
            av_Cards.pop_back();
        }
        players.push_back({ m_user->getUsername(),*first_cards });
    }
    GameData response_data;
    for (auto& player : other_players) {
        response_data.players.push_back(player);
    }
    for (auto& card : crds) {
        response_data.cards.push_back(card);
    }
    response_data.turn = name_temp;
    response_data.placed_card = current_card;

    return response_data;
}


//function will check if its allowed to place a card in the middle. if it is allowed, it will place it and make all of the changes.
//then it will return true or false if it did it or not.
bool Game::tryPlacement(Card card) {
    if (players[current_player].name ==m_user->getUsername() && current_card.what != "Draw") {
        if (current_card.color=="None" && last_card.color == "None") {
            current_card = card;
            last_card = card;
            players[current_player].cards.erase(std::remove(players[current_player].cards.begin(), players[current_player].cards.end(), card), players[current_player].cards.end());
            if (card.what == "Skip") {
                current_player = (current_player + 2) % players.size();
                current_card = { "None","None" };
                last_card = card;
            }
            else {
                current_player = (current_player + 1) %players.size();
            }
            av_Cards.push_back(card);
            shuffleCards(av_Cards);
            return true;
        }
        else if (current_card.what!="None" && current_card.what == card.what || current_card.color == card.color) {
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
            return true;
        }
    }
    return false;
}



