using GUI.DataTypes;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using System.Threading;
using System.Web.UI;
using System.Windows.Forms;
using TakiClient;

namespace GUI.Forms
{
    internal static class ObsessiveDataRefresher
    {
        private static Thread DataUpdater;
        private static bool autoRefreshRunning;
        private const int AutoRefreshSeconds = 3;

        static ObsessiveDataRefresher()
        {
            autoRefreshRunning = false;
        }

        public static void AutoRefreshData(Form form)
        {
            if (!autoRefreshRunning)
            {
                autoRefreshRunning = true;
                DataUpdater = new Thread(new ParameterizedThreadStart(UpdateData));
                DataUpdater.Start(form);
            }
        }

        public static void CreateRoomForm(string name, int id)
        {
            StopAutoRefreshData();
            string sendCreateRoomMsg = TakiProtocol.CreateRoom(name, id);
            Socket.SendMsg(sendCreateRoomMsg);

            string recvCreateRoomMsg = Socket.RecvMsgByResponse((int)TakiResponse.CREATE_ROOM);
            if (recvCreateRoomMsg != null)
            {
                MessageBox.Show("Room Successfully created", "Server Response", MessageBoxButtons.OK, MessageBoxIcon.Information);

                RoomParticipant menu = new RoomParticipant(name, true);
                menu.ShowDialog();

            }
        }

        public static void StopAutoRefreshData()
        {
            autoRefreshRunning = false;
            DataUpdater.Abort();
        }

        public static void UpdateData(object form)
        {
            try
            {
                while (autoRefreshRunning)
                {
                    if (form is Rooms joinRoom)
                    {
                        RoomsDataUpdater.UpdateRooms(joinRoom);
                    }
                    else if (form is RoomParticipant waitingForGame)
                    {
                        try
                        {
                            string roomData = GetCurrentRoomState();
                            RoomDataUpdater.UpdateUsers(waitingForGame, roomData);
                        }
                        catch (RoomClosedException)
                        {
                            autoRefreshRunning = false;
                            MessageBox.Show("The room was closed by the admin", "Leaving Room...", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            waitingForGame.Invoke(new MethodInvoker(delegate
                            {
                                waitingForGame.ExitMenu();
                            }));
                        }
                        catch (GameStartedException)
                        {
                            autoRefreshRunning = false;
                            waitingForGame.Invoke(new MethodInvoker(delegate
                            {
                                waitingForGame.StartGameForm();
                            }));
                        }
                    }
                    Thread.Sleep(AutoRefreshSeconds * 1000);
                }
            }
            catch
            {

            }
        }

        public static string GetCurrentRoomState()
        {
            try
            {
                string sendRoomStateMsg = TakiProtocol.GetCurrentRoomState();
                Socket.SendMsg(sendRoomStateMsg);

                string recvRoomStateMsg = Socket.RecvMsgByResponse((int)TakiResponse.GET_ROOM_STATE, (int)TakiResponse.LEAVE_ROOM, (int)TakiResponse.START_GAME);

                if (recvRoomStateMsg != null)
                {
                    TakiMessage roomStateMessage = new TakiMessage(int.Parse(recvRoomStateMsg.Substring(0,3)), recvRoomStateMsg.Substring(3));

                    switch (roomStateMessage.Code)
                    {
                        case (int)TakiResponse.GET_ROOM_STATE:
                            return recvRoomStateMsg;

                        case (int)TakiResponse.LEAVE_ROOM:
                            throw new RoomClosedException();

                        case (int)TakiResponse.START_GAME:
                            throw new GameStartedException();
                    }
                }
                return null;
            }
            catch
            {
                return null;
            }
        }

        public static List<string> ProcessJsonPlayers(string json)
        {
            // Extract the JSON part
            json = json.Substring(json.IndexOf('{'));
            JObject jObject = JObject.Parse(json);
            string playersString = (string)jObject["players"];
            string[] playersArray = playersString.Split(',');

            List<string> playerStrings = new List<string>();
            for (int i = 0; i < playersArray.Length; i++)
            {
                string playerString = $"PLAYER {i + 1}: {playersArray[i].Trim()}";
                playerStrings.Add(playerString);
            }

            return playerStrings;
        }

        internal static class RoomsDataUpdater
        {
            private static string selectedRoomName;

            static RoomsDataUpdater()
            {
                selectedRoomName = "";
            }

            internal static void UpdateRooms(Rooms form)
            {
                string roomName;
                int roomIndex;

                if (autoRefreshRunning)
                {
                    form.Invoke(new MethodInvoker(delegate
                    {
                        selectedRoomName = form.RoomList.GetItemText(form.RoomList.SelectedItem);
                        form.RoomList.Items.Clear();

                        List<string> rooms = ProcessJsonToString();
                        if (rooms != null)
                        {
                            foreach (var room in rooms)
                            {
                                roomName = room.ToString();
                                roomIndex = form.RoomList.Items.Add(roomName);

                                if (roomName == selectedRoomName)
                                    form.RoomList.SelectedIndex = roomIndex;
                            }
                        }
                    }));
                }
            }


            public static List<string> ProcessJsonToString()
            {
                string sendRoomsMsg = TakiProtocol.GetRooms();
                Socket.SendMsg(sendRoomsMsg);

                string recvRoomsMsg = Socket.RecvMsgByResponse((int)TakiResponse.GET_ROOMS);

                int statusCode = Int32.Parse(recvRoomsMsg.Substring(0, recvRoomsMsg.IndexOf('{')));

                // Extract the JSON part
                recvRoomsMsg = recvRoomsMsg.Substring(recvRoomsMsg.IndexOf('{'));
                JObject jObject = JObject.Parse(recvRoomsMsg);
                JArray rooms = (JArray)jObject["rooms"];

                List<string> roomStrings = new List<string>();

                foreach (var room in rooms)
                {
                    string roomString = string.Format(
                        "Room ID: {0}  |  Room Name: {1}  |  Max Number Of Players: {2}  |  Is Active: {3}",
                        room[1], // id
                        room[3], // name
                        room[5], // max_players
                        room[7]  // is_active
                    );

                    roomStrings.Add(roomString);
                }

                return roomStrings;
            }
        }

            internal static class RoomDataUpdater
            {
                internal static void UpdateUsers(RoomParticipant form, string data)
                {
                    try
                    {
                        if (autoRefreshRunning)
                        {
                            List<string> players = ProcessJsonPlayers(data);
                            form.Invoke(new MethodInvoker(delegate
                            {
                                form.RoomList.Items.Clear();

                                foreach (var player in players)
                                {
                                    form.RoomList.Items.Add(player);
                                }
                                form.RoomList.Items[0] = form.RoomList.Items[0].ToString() + " - ADMIN";
                            }));
                        }
                    }
                    catch
                    {

                    }
                }
            }
        }
    }

