using System.Windows.Forms;
using System;


namespace GUI
{
    partial class Login
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
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // name_label
            // 
            this.name_label.Location = new System.Drawing.Point(344, 185);
            this.name_label.Name = "name_label";
            this.name_label.Size = new System.Drawing.Size(90, 18);
            this.name_label.TabIndex = 0;
            this.name_label.Text = "Username:";
            // 
            // pass_label
            // 
            this.pass_label.Location = new System.Drawing.Point(344, 242);
            this.pass_label.Name = "pass_label";
            this.pass_label.Size = new System.Drawing.Size(90, 18);
            this.pass_label.TabIndex = 2;
            this.pass_label.Text = "Password:";
            // 
            // name_input
            // 
            this.name_input.Location = new System.Drawing.Point(344, 206);
            this.name_input.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.name_input.Name = "name_input";
            this.name_input.Size = new System.Drawing.Size(90, 26);
            this.name_input.TabIndex = 1;
            // 
            // pass_input
            // 
            this.pass_input.Location = new System.Drawing.Point(344, 263);
            this.pass_input.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pass_input.Name = "pass_input";
            this.pass_input.PasswordChar = '*';
            this.pass_input.Size = new System.Drawing.Size(90, 26);
            this.pass_input.TabIndex = 3;
            // 
            // login_button
            // 
            this.login_button.Location = new System.Drawing.Point(344, 292);
            this.login_button.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.login_button.Name = "login_button";
            this.login_button.Size = new System.Drawing.Size(90, 38);
            this.login_button.TabIndex = 4;
            this.login_button.Text = "Login";
            this.login_button.Click += new System.EventHandler(this.Login_Button_Click);
            // 
            // signup_button
            // 
            this.signup_button.Location = new System.Drawing.Point(330, 335);
            this.signup_button.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.signup_button.Name = "signup_button";
            this.signup_button.Size = new System.Drawing.Size(119, 38);
            this.signup_button.TabIndex = 5;
            this.signup_button.Text = "Sign Up";
            this.signup_button.Click += new System.EventHandler(this.Signup_Button_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::GUI.Properties.Resources.logo_with_text;
            this.pictureBox1.Location = new System.Drawing.Point(243, 55);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(302, 127);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 6;
            this.pictureBox1.TabStop = false;
            // 
            // Login
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(849, 477);
            this.Controls.Add(this.name_label);
            this.Controls.Add(this.name_input);
            this.Controls.Add(this.pass_label);
            this.Controls.Add(this.pass_input);
            this.Controls.Add(this.login_button);
            this.Controls.Add(this.signup_button);
            this.Controls.Add(this.pictureBox1);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Login";
            this.Text = "FullsTaki";
            this.Load += new System.EventHandler(this.Login_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        private void Login_Button_Click(object sender, EventArgs e)
        {
            string username = name_input.Text;
            string password = pass_input.Text;

            //ohad backend goes here
            MessageBox.Show("Login attempt with username: " + username + " Ohad add server pls");

             // if code == 101
                MainMenu menu = new MainMenu();
                this.Hide();
                menu.Show();
            //else MessageBox.Show(errormsg.tostring);
        }

        private void Signup_Button_Click(object sender, EventArgs e)
        {
           /*
             // if code == 101
                Signup signup_page = new Signup();
                this.Hide();
                signup_page.Closed += (s, args) => this.Close(); //https://stackoverflow.com/questions/5548746/c-sharp-open-a-new-form-then-close-the-current-form 
                signup_page.show();
            //else MessageBox.Show(errormsg.tostring);
            */
        
        }
        #endregion

        private PictureBox pictureBox1;
    }
}
