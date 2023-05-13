#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "ResponseTypes.hpp"
#include "incs.h"
//found this json library online
#include "json.hpp"
using json = nlohmann::json;
//--------------------------

//using specific functions from the std namespace
using std::cout;
using std::endl;
using std::vector;
using std::string;

/*
The JsonResponsePacketSerializer class is responsible for serializing different response types into
JSON format and constructing packets for data transfer.
*/
class JsonResponsePacketSerializer
{

public:
	
	static vector<char> serializeResponse(const ErrorResponse response);

	static vector<char> serializeResponse(const LoginResponse response);

	static vector<char> serializeResponse(const SignupResponse response);


private:

	static vector<char> responseBuilder(const int response_code, const string sData);
};
