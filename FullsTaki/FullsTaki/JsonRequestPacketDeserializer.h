#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "RequestTypes.hpp"

//found this json library online
#include "json.hpp"
using json = nlohmann::json;
//--------------------------

//using specific functions from the std namespace
using std::cout;
using std::endl;
using std::vector;
using std::string;

class JsonRequestPacketDeserializer
{

public:

	static LoginRequest deserializeLoginRequest(const vector<unsigned char>& buffer);

	static SignupRequest deserializeSignupRequest(const vector<unsigned char>& buffer);

	static GetPlayersInRoomRequest deserializeGetPlayersInRoom(const vector<unsigned char>& buffer);
	static JoinRoomRequest desirializeJoinRoom(const vector<unsigned char>& buffer);
	static CreateRoomRequest deserializeCreateRoom(const vector<unsigned char>& buffer);
	static PlaceCardRequest deserializePlayCardRequest(const vector<unsigned char>& buffer);
private:
	static json parseJson(const vector<unsigned char>& buffer);
};
