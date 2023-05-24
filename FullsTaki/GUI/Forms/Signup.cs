using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

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

            //ohad backend goes here
            MessageBox.Show("signup attempt with mail: " + email + " Ohad add server pls");

            // if code == 101
            MainMenu menu = new MainMenu(username);
            this.Hide();
            menu.Show();
            //else MessageBox.Show(errormsg.tostring);
        }
    }
}
