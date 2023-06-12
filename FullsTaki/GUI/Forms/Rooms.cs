using GUI.DataTypes;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;
using TakiClient;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.StartPanel;

namespace GUI.Forms
{
    public partial class Rooms : Form
    {
        private Timer timer;

        public Rooms()
        {

            InitializeComponent();
            timer = new Timer();
            timer.Interval = 2000; //2 seconds
            timer.Tick += Timer_Tick;
            timer.Start();


            UpdateRooms();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            UpdateRooms();
        }

        private void UpdateRooms()
        {
            TakiMessage getrooms = new TakiMessage
            {
                Code = (int)TakiRequest.GET_ROOMS,
                Content = ""
            };

            TakiClient.Socket.SendMsg(getrooms.ToString());

            // Receive and parse your data here
            byte[] buffer = new byte[4];

            // Get the response code
            NetworkStream stream = TakiClient.Socket.getSocket().GetStream();

            stream.Read(buffer, 0, 4);
            int responseCode = BitConverter.ToInt32(buffer, 0);
           /* if (responseCode != 100)
            {
                MainMenu menu = new MainMenu();
                this.Hide();
                menu.Show();
            }*/
            stream.Read(buffer, 0, 4);
            int responseLength = BitConverter.ToInt32(buffer, 0);

            buffer = new byte[responseLength];
            stream.Read(buffer, 0, responseLength);
            if(responseLength> 2)
            {
                string jsonString = Encoding.UTF8.GetString(buffer);
                //MessageBox.Show(jsonString);
                rooms = JsonConvert.DeserializeObject<Room[]>(jsonString);

                RoomList.Items.Clear();
                if (rooms != null)
                {
                    RoomList.Items.Add("|" + "Room ID".PadLeft(35).PadRight(67) + "|" + "Name".PadLeft(35).PadRight(70) + "|" + "Players".PadLeft(35).PadRight(70) + "|");
                    RoomList.Items.AddRange(rooms);
                }
                else
                {
                    RoomList.Items.Add("|" + "Room ID".PadLeft(35).PadRight(67) + "|" + "Name".PadLeft(35).PadRight(70) + "|" + "Players".PadLeft(35).PadRight(70) + "|");
                    RoomList.Items.Add("No rooms yet. create one!");
                }
            }


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
            int room_id = rooms[RoomList.SelectedIndex].id;

            //ohad backend goes here
            MessageBox.Show("Tryna join id="+room_id.ToString());
        }

        private void name_input_TextChanged(object sender, EventArgs e)
        {

        }

        private void name_label_Click(object sender, EventArgs e)
        {

        }

        private void login_button_Click(object sender, EventArgs e)
        {
            MessageBox.Show("create room" + name_input.Text + " Ohad add server pls");
        }

        private void Logout_Button_Click(object sender, EventArgs e)
        {
            Login menu = new Login();
            this.Hide();
            menu.Show();
        }

        private void Rooms_Load(object sender, EventArgs e)
        {

        }
    }
}
