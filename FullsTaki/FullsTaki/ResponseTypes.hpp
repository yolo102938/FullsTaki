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

typedef struct GameData {
	std::vector<Player> players;
	std::vector<Card> cards;
	std::string turn;
	Card placed_card;
	int status = 100;
}GameData;

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

typedef struct GetPersonalStatsResponse
{
	unsigned int status;
	vector<string> statistics;

	void print() const
	{
		cout << "Response Type: GetPersonalStatsResponse\nStatus: " + status << endl;
	}
} GetPersonalStatsResponse;

typedef struct LeaveGameResponse
{
	unsigned int status;

	void print() const
	{
		cout << "Response Type: LeaveGameResponse\nStatus: " + status << endl;
	}
} LeaveGameResponse;

struct PlayerResults
{
	string username;
	unsigned int cardsInHand;
	float averagePlayTime;
};

struct DrawCardFromDeckResponse
{
	unsigned int status;
	string card;
};

struct PlaceCardResponse
{
	unsigned int status;
};

struct GetGameResultsResponse
{
	unsigned int status;
	vector<PlayerResults> results;
};

struct CallLastCardInHandResponse
{
	unsigned int status;
};

typedef struct LogoutResponse
{
	unsigned int status;
} LogoutResponse;

typedef struct JoinRoomResponse
{
	unsigned int status;
} JoinRoomResponse;

typedef struct GetPlayersInRoomResponse
{
	vector<string> players;
} GetPlayersInRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
} CreateRoomResponse;

typedef struct GetRoomsResponse
{
	unsigned int status;
	vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct getHighScoreResponse
{
	unsigned int status;
	vector<string> statistics;
} getHighScoreResponse;


typedef struct StartGameResponse
{
    unsigned int status;
} StartGameResponse;

typedef struct CloseRoomResponse
{
    unsigned int status;
} CloseRoomResponse;

typedef struct GetRoomStateResponse
{
    unsigned int status;
    bool hasGameBegun;
    vector<string> players;
} GetRoomStateResponse;

typedef struct LeaveRoomResponse
{
    unsigned int status;

} LeaveRoomResponse;
