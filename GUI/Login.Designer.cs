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

        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

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
            this.SuspendLayout();
            // 
            // name_label
            // 
            this.name_label.Location = new System.Drawing.Point(300, 119);
            this.name_label.Name = "name_label";
            this.name_label.Size = new System.Drawing.Size(100, 23);
            this.name_label.TabIndex = 0;
            this.name_label.Text = "Username:";
            // 
            // pass_label
            // 
            this.pass_label.Location = new System.Drawing.Point(300, 190);
            this.pass_label.Name = "pass_label";
            this.pass_label.Size = new System.Drawing.Size(100, 23);
            this.pass_label.TabIndex = 2;
            this.pass_label.Text = "Password:";
            // 
            // name_input
            // 
            this.name_input.Location = new System.Drawing.Point(300, 145);
            this.name_input.Name = "name_input";
            this.name_input.Size = new System.Drawing.Size(100, 31);
            this.name_input.TabIndex = 1;
            // 
            // pass_input
            // 
            this.pass_input.Location = new System.Drawing.Point(300, 216);
            this.pass_input.Name = "pass_input";
            this.pass_input.PasswordChar = '*';
            this.pass_input.Size = new System.Drawing.Size(100, 31);
            this.pass_input.TabIndex = 3;
            // 
            // login_button
            // 
            this.login_button.Location = new System.Drawing.Point(300, 253);
            this.login_button.Name = "login_button";
            this.login_button.Size = new System.Drawing.Size(100, 47);
            this.login_button.TabIndex = 4;
            this.login_button.Text = "Login";
            // 
            // signup_button
            // 
            this.signup_button.Location = new System.Drawing.Point(284, 306);
            this.signup_button.Name = "signup_button";
            this.signup_button.Size = new System.Drawing.Size(132, 47);
            this.signup_button.TabIndex = 5;
            this.signup_button.Text = "Sign Up";
            // 
            // Login
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.name_label);
            this.Controls.Add(this.name_input);
            this.Controls.Add(this.pass_label);
            this.Controls.Add(this.pass_input);
            this.Controls.Add(this.login_button);
            this.Controls.Add(this.signup_button);
            this.Name = "Login";
            this.Text = "FullsTaki";
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        private void Login_Button_Click(object sender, EventArgs e)
        {
            string username = name_input.Text;
            string password = pass_input.Text;

            //ohad backend goes here

            MessageBox.Show("Login attempt with username: " + username+" Ohad add server pls");

        }

        private void Signup_Button_Click(object sender, EventArgs e)
        {
            /*
                 Signup signup_page = new Signup();
                 signup_page.show();
             */
        }
        #endregion
    }
}