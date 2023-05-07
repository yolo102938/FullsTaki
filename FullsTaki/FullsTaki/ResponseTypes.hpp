#pragma once
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

#define ERROR_RESPONSE 100
#define LOGIN_RESPONSE 101
#define SIGNUP_RESPONSE 102

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