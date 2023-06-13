﻿using GUI.DataTypes;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Security.Policy;
using System.Text;
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

        private Timer timer;

        public Rooms()
        {
            InitializeComponent();
            timer = new Timer();
            timer.Interval = 2000; //2 seconds
            timer.Tick += Timer_Tick;
            timer.Start();
            if (!comboBox2.DroppedDown)
            {
                int temp = comboBox2.SelectedIndex;
                UpdateRooms();
                comboBox2.SelectedIndex = temp;
            }
            
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

            
            if(true)
            {

                MSG msg = TakiClient.Socket.RecvMsg();
                //MessageBox.Show(jsonString);
                if(msg.code == 100)
                {

                    JArray jsonArray = (JArray)JObject.Parse(msg.json)["rooms"];
                    rooms = new List<Room>();

                    foreach (JArray roomArray in jsonArray)
                    {
                        int roomId = roomArray[1].Value<int>();
                        string name = roomArray[3].Value<string>();
                        int maxPlayers = roomArray[5].Value<int>();
                        int players = 0;
                        TakiMessage getplayercount = new TakiMessage
                        {
                            Code = (int)TakiRequest.GET_USERS_IN_ROOM,
                            Content = "{\"room_id\":" + roomId.ToString() + "}"
                        };

                        TakiClient.Socket.SendMsg(getplayercount.ToString());
                        string tmp = TakiClient.Socket.RecvMsg().json;
                        JArray players_ = ((JArray)JObject.Parse(tmp)["players"]);
                        players = players_.Count;
                        //add later getplayers inroom request
                        if (roomArray[7].Value<int>() != 1)
                        {
                            rooms.Add(new Room(name, roomId, maxPlayers, players));
                        }
                    }
                    index = comboBox2.SelectedIndex;
                    comboBox2.Items.Clear();
                    
                    RoomList.Items.Clear();
                    if (rooms.Count!=0)
                    {
                        RoomList.Items.Add("|" + "Room ID".PadLeft(35).PadRight(65) + "|" + "Name".PadLeft(35).PadRight(70) + "|" + "Players".PadLeft(35).PadRight(70) + "|");
                        RoomList.Items.AddRange(rooms.ToArray());
                        foreach (Room room in rooms)
                        {
                            comboBox2.Items.Add(room.name);
                        }
                        try { comboBox2.SelectedIndex = index; }
                        catch(Exception e) { }
                    }
                    else
                    {
                        RoomList.Items.Add("|" + "Room ID".PadLeft(35).PadRight(66) + "|" + "Name".PadLeft(35).PadRight(70) + "|" + "Players".PadLeft(35).PadRight(70) + "|");
                        RoomList.Items.Add("                \n\n\n\n\n                              No rooms at the moment. Create one!");
                    }
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

        private void pass_label_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {

            string sendLoginMsg = TakiClient.TakiProtocol.CreateRoom(name_input.Text, int.Parse((string)comboBox1.SelectedItem));
            TakiClient.Socket.SendMsg(sendLoginMsg);

            MSG recv = TakiClient.Socket.RecvMsg();
            if (recv.code != 101)
            {
                MessageBox.Show("Successfully created room", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
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

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            index = comboBox1.SelectedIndex;
        }
    }
}
