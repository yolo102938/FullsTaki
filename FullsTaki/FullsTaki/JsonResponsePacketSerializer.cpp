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
	return response;
}
