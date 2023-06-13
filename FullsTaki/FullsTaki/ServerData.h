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
*			 return codes:            *
*       100 - generic OK              *
*       666 - generic ERROR           *
*									  *
*									  *
*									  *
*									  *
*									  *
*									  *
*           account stuff:100		  *
*		100 - signup request          *
*		101 - login request           *
*		102 - logout request          *
*                                     *
*                                     *
*			room stuff:200            *
*       200 - get all the rooms       *
*       201 - create room             *
*       202 - join room               *
*       203 - get players in room     *
*                                     *
*                                     *
*                                     *
*                                     *
*                                     *
**************************************/
#define PORT_NUM 888
#define IP_ADDR "127.0.01"

#define SIGNUP_REQUEST 100
#define LOGIN_REQUEST 101
#define LOGOUT_REQUEST 102

#define GETROOMS_REQUEST 200
#define CREATEROOM_REQUEST 201 
#define JOINROOM_REQUEST 202 
#define GETPARTICIPANTS_REQUEST 203

#define CLOSEROOM_REQUEST 300
#define STARTGAME_REQUEST 301
#define LEAVEROOM_REQUEST 303

#define GETROOMSTATE_REQUEST 333



#define GENERIC_OK 100
#define ERROR_RESPONSE 101
#define LOGIN_RESPONSE 102
#define SIGNUP_RESPONSE 103

