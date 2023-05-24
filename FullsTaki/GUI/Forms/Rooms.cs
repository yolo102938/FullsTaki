using GUI.DataTypes;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;

namespace GUI.Forms
{
    public partial class Rooms : Form
    {
        public Rooms()
        {

            InitializeComponent();
            int listlen = 3;
            rooms = new Room[listlen];
            rooms[0] = (new GUI.DataTypes.Room() { name = "temp ohad do it",id= 1,max_players= 5,player_count= 4 });
            rooms[1] = (new GUI.DataTypes.Room() { name = "temp ohadf do it",id= 2,max_players= 5,player_count= 3 });
            rooms[2] = (new GUI.DataTypes.Room() { name = "temp ohaad do it",id= 3,max_players= 4,player_count= 4 });
            RoomList.Items.Add(("|" + "Room ID".ToString().PadLeft(35).PadRight(67) + "|" + "Name".PadLeft(35).PadRight(70) + "|" + ("Players").PadLeft(35).PadRight(70) + "|"));
            RoomList.Items.AddRange(rooms);     

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

        }
    }
}
