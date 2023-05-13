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