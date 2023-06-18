namespace GUI.Forms
{
    public enum TakiRequest
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
    }
}
