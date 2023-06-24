namespace TakiClient
{
    public enum TakiResponse
    {
        ERROR = 101,
        LOGIN,
        SIGNUP,
        LOGOUT,
        GET_ROOMS,
        GET_PLAYERS,
        GET_HIGHSCORE,
        GET_PERSONAL_STATS,
        JOIN_ROOM,
        CREATE_ROOM,
        CLOSE_ROOM,
        START_GAME,
        GET_ROOM_STATE,
        LEAVE_ROOM,
        LEAVE_GAME,
        PLAY_CARD_ANSWER,
        GET_GAME_STATE,
        GET_GAME_RESULT,
        SUCCESS = 1,
        FAIL = 0
    }
}
