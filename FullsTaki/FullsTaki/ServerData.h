#pragma once
/**************************************
*                                    *
*       Server Protocol Summery      *
*                                    *
***************************************
*                                     *
* This Server runs on TCP on port 888 *
* First Byte is the message code      *
* Next four bytes are the length      *
* Then the rest is json both ways     *
*                                     *
*                                     *
*                                     *
* 100 - signup request                *
* 101 - login request                 *
*  102 - logout request               *
*                                     *
**************************************/
#define PORT_NUM 888
#define IP_ADDR "1.1.1.1"

#define SIGNUP_REQUEST 100
#define LOGIN_REQUEST 101
#define LOGOUT_REQUEST 102

#define ERROR_RESPONSE 666
#define LOGIN_RESPONSE 101
#define SIGNUP_RESPONSE 102