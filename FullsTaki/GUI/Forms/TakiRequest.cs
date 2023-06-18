namespace GUI.Forms
{
    public enum TakiRequest
    {
        SIGN_UP = 100,
        LOGIN,
        LOGOUT,
        CREATE_ROOM = 201,
        GET_ROOMS = 200,
        GET_USERS_IN_ROOM = 203,
        JOIN_ROOM,
        CLOSE_ROOM = 300,
        START_GAME,
        GET_ROOM_STATE = 333,
        LEAVE_ROOM = 303,
        LEAVE_GAME,
        GET_GAME_RESULT,
        GET_GAME_STATE = 777,
        CARD_BANK_PREMISION = 701,
        EXIT_CLIENT = 400
    }
}
