#pragma once
#include "ServerData.h"
#include <iostream>
#include <vector>
#include <string>
#include "Room.h"
using std::cout;
using std::endl;
using std::string;


typedef struct ErrorResponse
{
	string message;

	void print() const
	{
		cout << "Response Type: ErrorResponse\nError Message: " + message << endl;
	}
} ErrorResponse;

typedef struct LoginResponse
{
	unsigned int status;

	void print() const
	{
		cout << "Response Type: LoginResponse\nStatus: " + status << endl;
	}
} LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;

	void print() const
	{
		cout << "Response Type: SignupResponse\nStatus: " + status << endl;
	}
} SignupResponse;

typedef struct LogoutResponse {
	unsigned int status;
} LogoutResponse;

typedef struct JoinRoomResponse {
	unsigned int status;
} JoinRoomResponse;

typedef struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct CreateRoomResponse {
	unsigned int status;
} CreateRoomResponse;

typedef struct GetRoomsResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct getHighScoreResponse {
	unsigned int status;
	std::vector<std::string> statistics;
} getHighScoreResponse;


typedef struct StartGameResponse {
    unsigned int status;
} StartGameResponse;

typedef struct CloseRoomResponse {
    unsigned int status;
} CloseRoomResponse;

typedef struct GetRoomStateResponse {
    unsigned int status;
    bool hasGameBegun;
    std::vector<std::string> players;

} GetRoomStateResponse;

typedef struct LeaveRoomResponse {
    unsigned int status;

} LeaveRoomResponse;
