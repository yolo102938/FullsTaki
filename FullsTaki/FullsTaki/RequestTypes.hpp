#pragma once
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

#define SIGNUP_REQUEST 100
#define LOGIN_REQUEST 101

typedef struct SignupRequest
{
	string username;
	string password;
	string email;
	string address;
	string phoneNumber;
	string birthDate;

	void print() const
	{
		cout << "Request Type: SignupRequest\nusername: " + username + "\npassword: " + password + "\nemail: " + email +
			"\naddress: " + address + "\nphone number: " + phoneNumber + "\nbirth date:" + birthDate << endl;
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