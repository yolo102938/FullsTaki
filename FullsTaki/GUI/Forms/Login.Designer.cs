using System.Windows.Forms;
using System;
using TakiClient;
using System.Runtime;
using GUI;

namespace GUI.Forms
{
    public partial class Login : Form
    {

        private Label name_label;
        private Label pass_label;
        private TextBox name_input;
        private TextBox pass_input;
        private Button login_button;
        private Button signup_button;
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }


        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>


        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.name_label = new System.Windows.Forms.Label();
            this.pass_label = new System.Windows.Forms.Label();
            this.name_input = new System.Windows.Forms.TextBox();
            this.pass_input = new System.Windows.Forms.TextBox();
            this.login_button = new System.Windows.Forms.Button();
            this.signup_button = new System.Windows.Forms.Button();
            this.FullLogo = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.FullLogo)).BeginInit();
            this.SuspendLayout();
            // 
            // name_label
            // 
            this.name_label.Location = new System.Drawing.Point(573, 320);
            this.name_label.Name = "name_label";
            this.name_label.Size = new System.Drawing.Size(87, 19);
            this.name_label.TabIndex = 0;
            this.name_label.Text = "Username:";
            this.name_label.Click += new System.EventHandler(this.name_label_Click);
            // 
            // pass_label
            // 
            this.pass_label.Location = new System.Drawing.Point(573, 376);
            this.pass_label.Name = "pass_label";
            this.pass_label.Size = new System.Drawing.Size(97, 21);
            this.pass_label.TabIndex = 2;
            this.pass_label.Text = "Password:";
            // 
            // name_input
            // 
            this.name_input.Location = new System.Drawing.Point(510, 341);
            this.name_input.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.name_input.Name = "name_input";
            this.name_input.Size = new System.Drawing.Size(205, 26);
            this.name_input.TabIndex = 1;
            // 
            // pass_input
            // 
            this.pass_input.Location = new System.Drawing.Point(510, 399);
            this.pass_input.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pass_input.Name = "pass_input";
            this.pass_input.PasswordChar = '*';
            this.pass_input.Size = new System.Drawing.Size(205, 26);
            this.pass_input.TabIndex = 3;
            // 
            // login_button
            // 
            this.login_button.Location = new System.Drawing.Point(510, 437);
            this.login_button.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.login_button.Name = "login_button";
            this.login_button.Size = new System.Drawing.Size(214, 70);
            this.login_button.TabIndex = 4;
            this.login_button.Text = "Login";
            this.login_button.Click += new System.EventHandler(this.Login_Button_Click);
            // 
            // signup_button
            // 
            this.signup_button.Location = new System.Drawing.Point(510, 511);
            this.signup_button.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.signup_button.Name = "signup_button";
            this.signup_button.Size = new System.Drawing.Size(214, 68);
            this.signup_button.TabIndex = 5;
            this.signup_button.Text = "Sign Up";
            this.signup_button.Click += new System.EventHandler(this.Signup_Button_Click);
            // 
            // FullLogo
            // 
            this.FullLogo.Image = global::GUI.Properties.Resources.logo_with_text;
            this.FullLogo.Location = new System.Drawing.Point(302, 12);
            this.FullLogo.Name = "FullLogo";
            this.FullLogo.Size = new System.Drawing.Size(615, 275);
            this.FullLogo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.FullLogo.TabIndex = 6;
            this.FullLogo.TabStop = false;
            // 
            // Login
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1231, 622);
            this.Controls.Add(this.name_label);
            this.Controls.Add(this.name_input);
            this.Controls.Add(this.pass_label);
            this.Controls.Add(this.pass_input);
            this.Controls.Add(this.login_button);
            this.Controls.Add(this.signup_button);
            this.Controls.Add(this.FullLogo);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Login";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "FullsTaki";
            this.Load += new System.EventHandler(this.Login_Load);
            ((System.ComponentModel.ISupportInitialize)(this.FullLogo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        private void Login_Button_Click(object sender, EventArgs e)
        {
            if (!Source.CheckInput(Controls))
            {
                MessageBox.Show("You must fill all fields to continue", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            string sendLoginMsg = TakiClient.TakiProtocol.Login(name_input.Text, pass_input.Text);
            TakiClient.Socket.SendMsg(sendLoginMsg);

            string recvLoginMsg = Socket.RecvMsgByResponse((int)TakiResponse.LOGIN);
            if (recvLoginMsg != null)
            {
                MessageBox.Show("Successfully logged in", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
                Socket.LoggedUser = name_input.Text;
                Socket.LoggedUserPass = pass_input.Text;
                Text += Socket.LoggedUserFormatted;
                MainMenu mainM = new MainMenu(name_input.Text);
                this.Hide();
                mainM.Show();
            }
        }

        private void Signup_Button_Click(object sender, EventArgs e)
        {
            Signup menu = new Signup();
            this.Hide();
            menu.Show();
        }
        #endregion

        private PictureBox FullLogo;
    }
}
