#include "JsonResponsePacketSerializer.h"

/*
Function serializes an ErrorResponse object into a json formatted vector of characters.
Input: const ErrorResponse response (An ErrorResponse object).
Output: vector<char> response (A serialized json response as a vector of chars).
*/
vector<char> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse response)
{
	//creating a json object with a "message" key and the error message as its value.
	json sData = { {"message", response.message} };

	//calling the responseBuilder function with the ERROR_RESPONSE status code and the serialized json data.
	return responseBuilder(ERROR_RESPONSE, sData.dump());
}

/*
Function serializes a LoginResponse object into a json formatted vector of characters.
Input: const LoginResponse response (A LoginResponse object).
Output: vector<char> response (A serialized json response as a vector of chars).
*/
vector<char> JsonResponsePacketSerializer::serializeResponse(const LoginResponse response)
{
	//creating a json object with a "status" key and the login status as its value.
	json sData = { {"status", response.status} };

	//calling the responseBuilder function with the login status code and the serialized json data.
	return responseBuilder(response.status, sData.dump());
}

/*
Function serializes a SignupResponse object into a json formatted vector of characters.
Input: const SignupResponse response (A SignupResponse object).
Output: vector<char> response (A serialized json response as a vector of chars).
*/
vector<char> JsonResponsePacketSerializer::serializeResponse(const SignupResponse response)
{
	//creating a json object with a "status" key and the signup status as its value.
	json sData = { {"status", response.status} };

	//calling the responseBuilder function with the signup status code and the serialized json data.
	return responseBuilder(response.status, sData.dump());
}

/*
Function serializes a LogoutResponse object into a json formatted vector of characters.
Input: const LogoutResponse response (A LogoutResponse object).
Output: vector<char> response (A serialized json response as a vector of chars).
*/
vector<char> JsonResponsePacketSerializer::serializeResponse(const LogoutResponse response)
{
	json sData = { {"status", response.status} };

	return responseBuilder(response.status, sData.dump());
}

/*
Function serializes a JoinRoomResponse object into a json formatted vector of characters.
Input: const JoinRoomResponse response (A JoinRoomResponse object).
Output: vector<char> response (A serialized json response as a vector of chars).
*/
vector<char> JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse response)
{
	json sData = { {"status", response.status} };

	return responseBuilder(response.status, sData.dump());
}

/*
Function serializes a GetPlayersInRoomResponse object into a json formatted vector of characters.
Input: const GetPlayersInRoomResponse response (A GetPlayersInRoomResponse object).
Output: vector<char> response (A serialized json response as a vector of chars).
*/
vector<char> JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse response)
{
	json sData = { {"players", response.players} };

	return responseBuilder(GENERIC_OK, sData.dump());  // Assuming a SUCCESS_RESPONSE constant for successful responses
}

/*
Function serializes a CreateRoomResponse object into a json formatted vector of characters.
Input: const CreateRoomResponse response (A CreateRoomResponse object).
Output: vector<char> response (A serialized json response as a vector of chars).
*/
vector<char> JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse response)
{
	json sData = { {"status", response.status} };

	return responseBuilder(response.status, sData.dump());
}

/*
Function serializes a GetRoomsResponse object into a json formatted vector of characters.
Input: const GetRoomsResponse response (A GetRoomsResponse object).
Output: vector<char> response (A serialized json response as a vector of chars).
*/
vector<char> JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse response)
{
	// Assuming RoomData can be converted directly to a json object
	json rooms = json::array();
	for (const auto& room : response.rooms)
	{
	
		rooms.push_back({"id", room.id,"name",room.name,"max_players",room.maxPlayers,"is_active",room.isActive});
	}

	json sData = { {"status", response.status}, {"rooms", rooms} };

	return responseBuilder(response.status, sData.dump());
}

/*
Function serializes a getHighScoreResponse object into a json formatted vector of characters.
Input: const getHighScoreResponse response (A getHighScoreResponse object).
Output: vector<char> response (A serialized json response as a vector of chars).
*/
vector<char> JsonResponsePacketSerializer::serializeResponse(const getHighScoreResponse response)
{
	json sData = { {"status", response.status}, {"statistics", response.statistics} };
	//std::cout << "DONEDID\n";
	return responseBuilder(response.status, sData.dump());
}


vector<char> JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse& response)
{
	json sData;
	sData["status"] = response.status;
	return responseBuilder(response.status, sData.dump());
}

vector<char> JsonResponsePacketSerializer::serializeResponse(const StartGameResponse& response)
{
	json sData;
	sData["status"] = response.status;
	return responseBuilder(response.status, sData.dump());
}

vector<char> JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse& response)
{
	json sData;
	sData["status"] = response.status;
	sData["hasGameBegun"] = response.hasGameBegun;
	std::string user_line = "";
	for (auto name : response.players) {
		user_line = user_line + name + ",";
	}
	user_line.pop_back();
	sData["players"] = user_line;
	return responseBuilder(response.status, sData.dump());
}

vector<char> JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse& response)
{
	json sData;
	sData["status"] = response.status;
	return responseBuilder(response.status, sData.dump());
}

vector<char> JsonResponsePacketSerializer::serializeResponse(const LeaveGameResponse response)
{
	json serializedData = { {"status", response.status} };
	return responseBuilder(LEAVE_GAME_RESPONSE, serializedData.dump());
}


vector<char> JsonResponsePacketSerializer::serializeResponse(const PlaceCardResponse response)
{
	json serializedData = { {"status", response.status} };
	return responseBuilder(PLAY_CARD_RESPONSE, serializedData.dump());
}


vector<char> JsonResponsePacketSerializer::serializeResponse(const GameData& response)
{
	ordered_json jsonData;

	//player list
	std::vector<ordered_json> players;
	for (const auto& player : response.players)
	{
		ordered_json playerData;
		playerData["name"] = player.name;
		playerData["card_count"] = player.cards.size();
		players.push_back(playerData);
	}
	jsonData["players"] = players;

	//client cards
	std::vector<ordered_json> cards;
	for (const auto& card : response.cards)
	{
		ordered_json cardData;
		cardData["color"] = card.color;
		cardData["what"] = card.what;
		cards.push_back(cardData);
	}
	jsonData["cards"] = cards;

	//current turn
	jsonData["turn"] = response.turn;

	//current on top card
	ordered_json placedCard;
	if (response.placed_card.color != "none" && response.placed_card.color != "None") {
		placedCard["color"] = response.placed_card.color;
		placedCard["what"] = response.placed_card.what;
	}
	else {
		placedCard["color"] = "none";
		placedCard["what"] = "";
	}
	jsonData["placed_card"] = placedCard;
	return responseBuilder(response.status, jsonData.dump());
}


/*
Function constructs a response packet using a response status code and serialized json data.
Input: const int resStatusCode (The status code of the response), const string sData (The serialized json data as a string).
Output: vector<char> response (A response packet as a vector of chars).
*/
vector<char> JsonResponsePacketSerializer::responseBuilder(const int resStatusCode, const string sData)
{
	vector<char> response;
	//adding the status code (casted to char) as the first byte of the response vector.
	
	int resultCode = static_cast<int>(resStatusCode);
	resultCode = htonl(resultCode);
	const char* resCode = reinterpret_cast<const char*>(&resultCode);
	response.insert(response.end(),resCode, resCode + sizeof(resultCode));

	//converting the length of the json data into a 4 byte data and adding it to the response vector.
	int resultLen = static_cast<int>(sData.size());
	resultLen = htonl(resultLen);
	const char* resLen = (reinterpret_cast<const char*>(&(resultLen)));
	response.insert(response.end(), resLen, resLen + sizeof(resultLen));

	//adding the json data to the response packet.
	response.insert(response.end(), sData.begin(), sData.end());
	//returning the response packet.
	//std::cout << response.data();
	return response;
}
