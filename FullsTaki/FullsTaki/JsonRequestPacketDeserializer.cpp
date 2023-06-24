#include "jsonRequestPacketDeserializer.h"

/*
Function deserializes the given buffer to create a SignupRequest object.
The function extracts json data from the given buffer, parses it and initializes a SignupRequest object with the extracted data.
Input: const vector<byte>& buffer (A vector of unsigned chars containing the serialized data).
Output: A SignupRequest object with the deserialized data.
*/
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::vector<unsigned char>& buffer)
{
    //parsing json data from the buffer to a json object.
    json jsonData = parseJson(buffer);
    //initializing and returning a SignupRequest object with the extracted data.
    return SignupRequest({ jsonData["username"], jsonData["password"], jsonData["email"]});
}

/*
Function deserializes the given buffer to create a LoginRequest object.
The function extracts json data from the given buffer, parses it and initializes a LoginRequest object with the extracted data.
Input: const vector<byte>& buffer (A vector of unsigned chars containing the serialized data).
Output: A LoginRequest object with the deserialized data.
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<unsigned char>& buffer)
{
    //parsing json data from the buffer to a json object.
    json jsonData = parseJson(buffer);
    //initializing and returning a LoginRequest object with the extracted data.
    return LoginRequest({ jsonData["username"], jsonData["password"] });
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoom(const std::vector<unsigned char>& buffer)
{
    //parsing json data from the buffer to a json object.
    json jsonData = parseJson(buffer);
    //initializing and returning a SignupRequest object with the extracted data.
    return GetPlayersInRoomRequest({ jsonData["room_id"]});
}

JoinRoomRequest JsonRequestPacketDeserializer::desirializeJoinRoom(const vector<unsigned char>& buffer)
{
    string data(buffer.begin(), buffer.end());
    data = data.substr(data.find('{'));// get only the json part

    json jsonData = json::parse(data); // parse to json
    return JoinRoomRequest({ jsonData["roomId"] });
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoom(const std::vector<unsigned char>& buffer)
{
    //parsing json data from the buffer to a json object.
    json jsonData = parseJson(buffer);
    //initializing and returning a SignupRequest object with the extracted data.
    //std::cout<<(jsonData["max_users"]);
    return CreateRoomRequest({ jsonData["name"],jsonData["max_users"]});
}
/*
PlaceCardRequest JsonRequestPacketDeserializer::deserializePlayCardRequest(const vector<unsigned char>& buffer)
{
    string data(buffer.begin(), buffer.end());
    data = data.substr(data.find('{'));// get only the json part

    json jsonData = json::parse(data); // parse to json
    return PlaceCardRequest({ jsonData["cardId"] });
}
*/

string JsonRequestPacketDeserializer::deserializePlaceCard(const vector<unsigned char>& buffer)
{
    //parsing json data from the buffer to a json object.
    json jsonData = parseJson(buffer);
    std::string fullTag = jsonData["picture_tag"];

    //initializing and returning a SignupRequest object with the extracted data.
    return fullTag;
}

/*
Function parses json data from the given buffer.
The function creates a string from the buffer's data, locates the first '{' to get only the json data,
and then parses the data into a json object.
Input: const vector<byte>& buffer (A vector of unsigned chars containing the serialized data).
Output: A json object parsed from the given buffer.
*/
json JsonRequestPacketDeserializer::parseJson(const vector<unsigned char>& buffer)
{
    string data(buffer.begin(), buffer.end()); //creating a string with the buffer's data.
    data = data.substr(data.find('{')); //locating the first '{' to get only the json data.
    return json::parse(data); //parsing the data to a json object and returning it.
}