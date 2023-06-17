using GUI.Forms;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TakiClient;

namespace GUI
{
    public partial class MainMenu : Form
    {
        public MainMenu()
        {
            InitializeComponent();
        }
        public MainMenu(string name)
        {
            InitializeComponent(name);
        }
        private void button1_Click(object sender, EventArgs e)
        {
            Rooms menu = new Rooms();
            Hide();
            menu.ShowDialog();
            Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click_1(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {

            LogoutClient();
            Login menu = new Login();
            this.Hide();
            menu.Show();
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
        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void MainMenu_Load(object sender, EventArgs e)
        {

        }
    }
}
