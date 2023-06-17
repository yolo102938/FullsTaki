using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using System.Net.Sockets;
using GUI.Forms;
namespace TakiClient
{
    public static class TakiProtocol
    {

        public static string FormatResponseByMessage(string recvMsg)
        {
            TakiMessage message = new TakiMessage(recvMsg);
            Dictionary<string, string> mDic = message.ToDict();

            return mDic.ContainsKey("message") ? mDic["message"] : "";
        }

        public static string SignIn(string username, string password, string email)
        {
            Dictionary<string, string> jsonDictionary = new Dictionary<string, string>
            {
                { "username", username },
                { "password", password },
                { "email", email },
            };

            TakiMessage signUpMessage = new TakiMessage
            {
                Code = (int)TakiRequest.SIGN_UP,
                Content = JsonConvert.SerializeObject(jsonDictionary)
            };
            return signUpMessage.ToString();
        }

        public static string Login(string username, string password)
        {
            Dictionary<string, string> jsonDictionary = new Dictionary<string, string>
            {
                { "username", username },
                { "password", password }
            };

            TakiMessage loginMessage = new TakiMessage
            {
                Code = (int)TakiRequest.LOGIN,
                Content = JsonConvert.SerializeObject(jsonDictionary)
            };
            return loginMessage.ToString();
        }
        public static string CreateRoom(string name, int maxp)
        {
            Dictionary<string, object> jsonDictionary = new Dictionary<string, object>
    {
        { "name", name },
        { "max_users", maxp }
    };

            TakiMessage loginMessage = new TakiMessage
            {
                Code = (int)TakiRequest.CREATE_ROOM,
                Content = JsonConvert.SerializeObject(jsonDictionary)
            };

            return loginMessage.ToString();
        }
        public static string joinRoom( int id)
        {
            Dictionary<string, object> jsonDictionary = new Dictionary<string, object>
    {
        { "id", id }
    };

            TakiMessage loginMessage = new TakiMessage
            {
                Code = (int)TakiRequest.CREATE_ROOM,
                Content = JsonConvert.SerializeObject(jsonDictionary)
            };

            return loginMessage.ToString();
        }
        public static string Logout(string username, string password)
        {
            Dictionary<string, string> jsonDictionary = new Dictionary<string, string>
            {
                { "username", username },
                { "password", password }
            };

            TakiMessage loginMessage = new TakiMessage
            {
                Code = (int)TakiRequest.LOGOUT,
                Content = JsonConvert.SerializeObject(jsonDictionary)
            };
            return loginMessage.ToString();
        }

    }
}
