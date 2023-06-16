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

	static LoginRequest deserializeLoginRequest(const std::vector<unsigned char>& buffer);

	static SignupRequest deserializeSignupRequest(const std::vector<unsigned char>& buffer);

	static GetPlayersInRoomRequest deserializeGetPlayersInRoom(const std::vector<unsigned char>& buffer);
	static JoinRoomRequest deserializeJoinRoom(const std::vector<unsigned char>& buffer);
	static CreateRoomRequest deserializeCreateRoom(const std::vector<unsigned char>& buffer);
private:
	static json parseJson(const std::vector<unsigned char>& buffer);
};
