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

typedef enum TakiRequest
{
    SIGN_UP = 100,
    LOGIN,
    LOGOUT,
    GET_ROOMS = 200,
    CREATE_ROOM,
    GET_USERS_IN_ROOM,
    JOIN_ROOM,
    CLOSE_ROOM,
    START_GAME,
    GET_ROOM_STATE,
    LEAVE_ROOM,
    LEAVE_GAME,
    GET_GAME_RESULT,
    EXIT_CLIENT = 250
} TakiRequest;

typedef enum TakiResponse
{
    ERROR_RESPONSE = 101,
    LOGIN_RESPONSE,
    SIGNUP_RESPONSE,
    LOGOUT_RESPONSE,
    GET_ROOMS_RESPONSE,
    GET_PLAYERS_RESPONSE,
    GET_HIGHSCORE_RESPONSE,
    GET_PERSONAL_STATS_RESPONSE,
    JOIN_ROOM_RESPONSE,
    CREATE_ROOM_RESPONSE,
    CLOSE_ROOM_RESPONSE,
    START_GAME_RESPONSE,
    GET_ROOM_STATE_RESPONSE,
    LEAVE_ROOM_RESPONSE,
    LEAVE_GAME_RESPONSE,
    GET_QUESTION_RESPONSE,
    SUBMIT_ANSWER_RESPONSE,
    GET_GAME_RESULT_RESPONSE,
    ADD_QUESTION_RESPONSE,
    SUCCESS_RESPONSE = 1,
    FAIL_RESPONSE = 0
} TakiResponse;

#define GENERIC_OK 100


