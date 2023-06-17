using GUI.DataTypes;
using System;
using System.Collections.Generic;
using System.Threading;
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
            DataUpdater.Abort();
            DataUpdater = null;
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
            DataUpdater.Abort();
            DataUpdater = null;
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
                            Dictionary<string, object> roomData = GetCurrentRoomState();
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

        public static Dictionary<string, object> GetCurrentRoomState()
        {
            try
            {
                string sendRoomStateMsg = TakiProtocol.GetCurrentRoomState();
                Socket.SendMsg(sendRoomStateMsg);

                string recvRoomStateMsg = Socket.RecvMsgByResponse((int)TakiResponse.GET_ROOM_STATE, (int)TakiResponse.LEAVE_ROOM, (int)TakiResponse.START_GAME);

                if (recvRoomStateMsg != null)
                {
                    TakiMessage roomStateMessage = new TakiMessage(recvRoomStateMsg);

                    switch (roomStateMessage.Code)
                    {
                        case (int)TakiRequest.GET_ROOM_STATE:
                            return roomStateMessage.ToMultiDict();

                        case (int)TakiRequest.LEAVE_ROOM:
                            throw new RoomClosedException();

                        case (int)TakiRequest.START_GAME:
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

        internal static class RoomsDataUpdater
        {
            private static string selectedRoomName;

            static RoomsDataUpdater()
            {
                selectedRoomName = "";
            }

            internal static void UpdateRooms(Rooms form)
            {
                try
                {
                    string roomName;
                    int roomIndex;

                    if (autoRefreshRunning)
                    {
                        form.Invoke(new MethodInvoker(delegate
                        {
                            selectedRoomName = form.RoomList.GetItemText(form.RoomList.SelectedItem);
                            form.RoomList.Items.Clear();

                            TakiMessage rooms = GetRooms();
                            if (rooms != null)
                            {
                                for (int i = 0; i < 1; i++)
                                {
                                    roomName = rooms.Content;
                                    roomIndex = form.RoomList.Items.Add(roomName);
                                    form.RoomList.Refresh();
                                    if (roomName == selectedRoomName)
                                        form.RoomList.SelectedIndex = roomIndex;
                                }
                            }
                        }));
                    }
                }
                catch
                {

                }
            }

            public static TakiMessage GetRooms()
            {
                try
                {
                    string sendRoomsMsg = TakiProtocol.GetRooms();
                    Socket.SendMsg(sendRoomsMsg);

                    string recvRoomsMsg = Socket.RecvMsgByResponse((int)TakiResponse.GET_ROOMS);
                    if (recvRoomsMsg != null)
                    {
                        TakiMessage roomsMessage = new TakiMessage(int.Parse(recvRoomsMsg.Substring(0,3)), recvRoomsMsg.Substring(3));
                        try
                        {
                            return roomsMessage;
                        }
                        catch
                        {
                            return null;
                        }
                    }
                    return null;
                }
                catch
                {
                    return null;
                }
            }
        }

        internal static class RoomDataUpdater
        {
            internal static void UpdateUsers(RoomParticipant form, Dictionary<string, object> data)
            {
                try
                {
                    if (autoRefreshRunning)
                    {
                        form.Invoke(new MethodInvoker(delegate
                        {
                            form.RoomList.Items.Clear();

                            foreach (string player in (object[])data["players"])
                            {
                                form.RoomList.Items.Add(player);
                            }
                            form.RoomList.Items[0] = form.RoomList.Items[0].ToString() + " - ADMIN"; // add crown sign to the first user in the list box (which is always the admin)
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
