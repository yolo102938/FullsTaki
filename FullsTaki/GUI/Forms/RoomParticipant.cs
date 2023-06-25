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
    public partial class RoomParticipant : Form
    {

        private static bool isAdmin;
        private bool IsAdmin
        {
            set
            {
                isAdmin = value;
                if (value)
                    button4.Visible = false;
                else
                {
                    button1.Visible = false;
                    button2.Visible = false;
                    button3.Visible = false;
                    label2.Visible = false;
                    comboBox2.Visible = false;
                }
            }
            get => isAdmin;
        }
        public static string RoomName { get; set; }

        public RoomParticipant(string roomName, bool admin)
        {
            InitializeComponent();
            RoomName = roomName;
            IsAdmin = admin;
            //ObsessiveDataRefresher.AutoRefreshData(this);
        }

        private void Refresh(object sender, EventArgs e)
        {
            try
            {
                ObsessiveDataRefresher.AutoRefreshData(this);
            }
            catch
            {
                ObsessiveDataRefresher.StopAutoRefreshData();
                StartGameForm();
            }
        }

        

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            int room_id = rooms[comboBox2.SelectedIndex].id;

            string sendLoginMsg = TakiClient.TakiProtocol.joinRoom(room_id);
            TakiClient.Socket.SendMsg(sendLoginMsg);

            MSG recv = TakiClient.Socket.RecvMsg();
            if (recv.code != 101)
            {
                MessageBox.Show("Successfully joined room", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
                //TakiClient.Socket.LoggedUser = name_input.Text;
                //Text += TakiClient.Socket.LoggedUserFormatted;
                //MainMenu mainM = new MainMenu(name_input.Text);
                //this.Hide();
                //mainM.Show();
            }
            else
            {

            }
        }

        private void name_input_TextChanged(object sender, EventArgs e)
        {

        }

        private void name_label_Click(object sender, EventArgs e)
        {

        }


        private void pass_label_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        internal void button2_Click(object sender, EventArgs e)
        {
            ObsessiveDataRefresher.StopAutoRefreshData();
            string sendStartGameMsg = TakiProtocol.StartGame();
            Socket.SendMsg(sendStartGameMsg);

            string recvStartGameMsg = Socket.RecvMsgByResponse((int)TakiResponse.START_GAME);
            if (recvStartGameMsg != null)
            {
                StartGameForm();
            }
        }


        public void StartGameForm()
        {
            ObsessiveDataRefresher.StopAutoRefreshData();
            GameRoom game = new GameRoom();
            Hide();
            game.ShowDialog();
            Close();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            index = comboBox2.SelectedIndex;
        }

        private void RoomAdmin_Load_1(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
        private void button4_Click(object sender, EventArgs e)
        {
            string sendLeaveRoomMsg = TakiProtocol.LeaveRoom();
            Socket.SendMsg(sendLeaveRoomMsg);

            string recvLeaveRoomMsg = Socket.RecvMsgByResponse((int)TakiResponse.LEAVE_ROOM);
            if (recvLeaveRoomMsg != null)
            {
                ObsessiveDataRefresher.StopAutoRefreshData();
                ExitMenu();
            }
        }
        internal void ExitMenu()
        {
            Hide();
            MainMenu menu = new MainMenu();
            menu.ShowDialog();
            Close();
        }

        private void CloseRoomButton_Click(object sender, EventArgs e)
        {
            string sendCloseRoomMsg = TakiProtocol.CloseRoom();
            Socket.SendMsg(sendCloseRoomMsg);

            string recvCloseRoomMsg = Socket.RecvMsgByResponse((int)TakiResponse.CLOSE_ROOM);
            if (recvCloseRoomMsg != null)
            {
                ObsessiveDataRefresher.StopAutoRefreshData();

                MessageBox.Show("Room successfully closed", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
                ExitMenu();
            }
        }
    }
}
