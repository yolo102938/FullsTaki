#pragma once
#include "ServerData.h"
#include <vector>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


class IRequestHandler;

typedef struct RequestInfo
{
	int id;
	time_t receivalTime;
	std::vector<unsigned char> buffer;
} RequestInfo;

typedef struct RequestResult
{
	std::vector<char> response;
	IRequestHandler *newHandler;
} RequestResult;

typedef struct SignupRequest
{
	string username;
	string password;
	string email;

	void print() const
	{
		cout << "Request Type: SignupRequest\nusername: " + username + "\npassword: " + password + "\nemail: " + email << endl;
	}
} SignupRequest;

typedef struct LoginRequest
{
	string username;
	string password;

	void print() const
	{
		cout << "Request Type: LoginRequest\nusername: " + username + "\npassword: " + password << endl;
	}
} LoginRequest;

typedef struct GetPlayersInRoomRequest{
	unsigned int roomId;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest {
	unsigned int roomId;
} JoinRoomRequest;

typedef struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
} CreateRoomRequest;