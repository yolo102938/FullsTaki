namespace GUI.Forms
{
    partial class Signup
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.name_label = new System.Windows.Forms.Label();
            this.name_input = new System.Windows.Forms.TextBox();
            this.pass_label = new System.Windows.Forms.Label();
            this.pass_input = new System.Windows.Forms.TextBox();
            this.login_button = new System.Windows.Forms.Button();
            this.signup_button = new System.Windows.Forms.Button();
            this.FullLogo = new System.Windows.Forms.PictureBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.FullLogo)).BeginInit();
            this.SuspendLayout();
            // 
            // name_label
            // 
            this.name_label.Location = new System.Drawing.Point(548, 298);
            this.name_label.Name = "name_label";
            this.name_label.Size = new System.Drawing.Size(87, 19);
            this.name_label.TabIndex = 7;
            this.name_label.Text = "Username:";
            // 
            // name_input
            // 
            this.name_input.Location = new System.Drawing.Point(485, 319);
            this.name_input.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.name_input.Name = "name_input";
            this.name_input.Size = new System.Drawing.Size(205, 26);
            this.name_input.TabIndex = 8;
            // 
            // pass_label
            // 
            this.pass_label.Location = new System.Drawing.Point(548, 347);
            this.pass_label.Name = "pass_label";
            this.pass_label.Size = new System.Drawing.Size(94, 28);
            this.pass_label.TabIndex = 9;
            this.pass_label.Text = "Password:";
            // 
            // pass_input
            // 
            this.pass_input.Location = new System.Drawing.Point(485, 377);
            this.pass_input.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pass_input.Name = "pass_input";
            this.pass_input.PasswordChar = '*';
            this.pass_input.Size = new System.Drawing.Size(205, 26);
            this.pass_input.TabIndex = 10;
            // 
            // login_button
            // 
            this.login_button.Location = new System.Drawing.Point(485, 561);
            this.login_button.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.login_button.Name = "login_button";
            this.login_button.Size = new System.Drawing.Size(214, 70);
            this.login_button.TabIndex = 11;
            this.login_button.Text = "Back to Login";
            this.login_button.Click += new System.EventHandler(this.login_button_Click);
            // 
            // signup_button
            // 
            this.signup_button.Location = new System.Drawing.Point(485, 489);
            this.signup_button.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.signup_button.Name = "signup_button";
            this.signup_button.Size = new System.Drawing.Size(214, 68);
            this.signup_button.TabIndex = 12;
            this.signup_button.Text = "Sign Up";
            this.signup_button.Click += new System.EventHandler(this.signup_button_Click);
            // 
            // FullLogo
            // 
            this.FullLogo.Image = global::GUI.Properties.Resources.logo_with_text;
            this.FullLogo.Location = new System.Drawing.Point(271, -10);
            this.FullLogo.Name = "FullLogo";
            this.FullLogo.Size = new System.Drawing.Size(615, 275);
            this.FullLogo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.FullLogo.TabIndex = 13;
            this.FullLogo.TabStop = false;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(485, 435);
            this.textBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(205, 26);
            this.textBox1.TabIndex = 14;
           
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(565, 405);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(94, 28);
            this.label1.TabIndex = 15;
            this.label1.Text = "Email:";
            // 
            // Signup
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1231, 622);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.name_label);
            this.Controls.Add(this.name_input);
            this.Controls.Add(this.pass_label);
            this.Controls.Add(this.pass_input);
            this.Controls.Add(this.login_button);
            this.Controls.Add(this.signup_button);
            this.Controls.Add(this.FullLogo);
            this.Name = "Signup";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.FullLogo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label name_label;
        private System.Windows.Forms.TextBox name_input;
        private System.Windows.Forms.Label pass_label;
        private System.Windows.Forms.TextBox pass_input;
        private System.Windows.Forms.Button login_button;
        private System.Windows.Forms.Button signup_button;
        private System.Windows.Forms.PictureBox FullLogo;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label1;
    }
}