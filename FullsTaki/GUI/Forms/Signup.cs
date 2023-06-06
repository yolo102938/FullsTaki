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

namespace GUI.Forms
{
    public partial class Signup : Form
    {
        public Signup()
        {
            InitializeComponent();
        }


        private void login_button_Click(object sender, EventArgs e)
        {
            Login menu = new Login();
            this.Hide();
            menu.Show();
        }

        private void signup_button_Click(object sender, EventArgs e)
        {
            string username = name_input.Text;
            string password = pass_input.Text;
            string email = textBox1.Text;

            if (!Source.CheckInput(Controls))
            {
                MessageBox.Show("You must fill all fields to continue", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string sendSignUpMsg = TakiProtocol.SignIn(username, password, email);
            Socket.SendMsg(sendSignUpMsg);

            string recvSignUpMsg = Socket.RecvMsgByResponse((int)TakiResponse.SIGNUP);
            if (recvSignUpMsg != null)
            {
                MessageBox.Show("Successfully signed up", "Server Response", MessageBoxButtons.OK, MessageBoxIcon.Information);
                MainMenu mainM = new MainMenu(name_input.Text);
                this.Hide();
                mainM.Show();
            }
        }
    }
}
