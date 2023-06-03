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

            //ohad backend goes here
            Login menu = new Login();
            this.Hide();
            menu.Show();
            //else MessageBox.Show(errormsg.tostring);
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void MainMenu_Load(object sender, EventArgs e)
        {

        }
    }
}
