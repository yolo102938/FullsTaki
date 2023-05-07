#pragma once
#include "IRequestHandler.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

#define SIGNUP_REQUEST 100
#define LOGIN_REQUEST 101

typedef struct RequestInfo
{
	int id;
	time_t receivalTime;
	vector<byte> buffer;
} RequestInfo;

typedef struct RequestResult
{
	vector<char> response;
	IRequestHandler* newHandler;
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