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

	static LoginRequest deserializeLoginRequest(const vector<byte>& buffer);

	static SignupRequest deserializeSignupRequest(const vector<byte>& buffer);

private:
	static json parseJson(const vector<byte>& buffer);
};
