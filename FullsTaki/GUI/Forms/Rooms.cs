using GUI.DataTypes;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;
using TakiClient;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.StartPanel;

namespace GUI.Forms
{
    public partial class Rooms : Form
    {

        public Rooms()
        {
            InitializeComponent();
            Text += Socket.LoggedUserFormatted;
        }

        private void Refresh(object sender, EventArgs e)
        {
            ObsessiveDataRefresher.AutoRefreshData(this);
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void RoomList_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            bool isGameAlreadyRunning = IsRoomActive(RoomList.SelectedItem.ToString());
            if (isGameAlreadyRunning)
            {
                string sendJoinMsg = TakiProtocol.JoinRoom(ExtractId(RoomList.SelectedItem.ToString()));
                Socket.SendMsg(sendJoinMsg);

                string recvJoinMsg = Socket.RecvMsgByResponse((int)TakiResponse.JOIN_ROOM);
                if (recvJoinMsg != null)
                {
                    ObsessiveDataRefresher.StopAutoRefreshData();

                    MessageBox.Show($"Successfuly joined to room: {RoomList.SelectedItem}", "Server Response", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    RoomParticipant menu = new RoomParticipant(ExtractName(RoomList.SelectedItem.ToString()), false);
                    Hide();
                    menu.ShowDialog();
                    Close();
                }
            }
            else
                MessageBox.Show("The game is already running in this room", "Can't Join", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        public static bool IsRoomActive(string roomName)
        {
            int first = roomName.IndexOf('e') + 3;
            int last = roomName.IndexOf('u') - 9;
            int len = last - first + 1;
            roomName = roomName.Substring(first, len);
            List<string> rooms = ObsessiveDataRefresher.RoomsDataUpdater.ProcessJsonToString();
            if (rooms != null)
            {
                foreach (var room in rooms)
                {
                    if (room.Contains(roomName))
                    {
                        int isActive = int.Parse(room[room.Length - 1].ToString());
                        return isActive == 1;
                    }
                }
            }
            return false;
        }

        public static int ExtractId(string roomString)
        {
            // The regular expression pattern to find the ID
            string pattern = @"Room ID: (\d+)";

            // Get the match object
            Match match = Regex.Match(roomString, pattern);

            // If the match is successful
            if (match.Success)
            {
                // Parse and return the ID
                return Int32.Parse(match.Groups[1].Value);
            }
            else
            {
                // If the ID is not found, throw an exception
                throw new Exception("No ID found in the room string.");
            }
        }

        public static string ExtractName(string roomString)
        {
            // The regular expression pattern to find the name
            string pattern = @"Room Name: ([^,]+)";

            // Get the match object
            Match match = Regex.Match(roomString, pattern);

            // If the match is successful
            if (match.Success)
            {
                // Return the name
                return match.Groups[1].Value.Trim();
            }
            else
            {
                // If the name is not found, throw an exception
                throw new Exception("No name found in the room string.");
            }
        }

        private void name_input_TextChanged(object sender, EventArgs e)
        {

        }

        private void name_label_Click(object sender, EventArgs e)
        {

        }

        private void Logout_Button_Click(object sender, EventArgs e)
        {
            LogoutClient();
        }
        private void LogoutClient()
        {
            if (Socket.Connected)
            {
                string sendLoginMsg = TakiClient.TakiProtocol.Logout(Socket.LoggedUser, Socket.LoggedUserPass);
                TakiClient.Socket.SendMsg(sendLoginMsg);

                string recvLoginMsg = Socket.RecvMsgByResponse((int)TakiResponse.LOGOUT);
                if (recvLoginMsg != null)
                {
                    MessageBox.Show("Successfully logged out", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    Login login = new Login();
                    this.Hide();
                    login.Show();
                }
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Hide();
            ObsessiveDataRefresher.CreateRoomForm(name_input.Text, 0);
            Close();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            index = comboBox1.SelectedIndex;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            MainMenu m = new MainMenu(Socket.LoggedUser);
            this.Hide();
            m.ShowDialog();
            Close();
            
        }
    }
}