namespace GUI
{
    partial class MainMenu
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
        private void InitializeComponent(string name)
        {
            InitializeComponent();
            this.Logged_Info_Label.Text = "Logged in as "+name;
        }
            #region Windows Form Designer generated code

            /// <summary>
            /// Required method for Designer support - do not modify
            /// the contents of this method with the code editor.
            /// </summary>
            private void InitializeComponent()
        {
            this.Rooms_Button = new System.Windows.Forms.Button();
            this.High_Score_Button = new System.Windows.Forms.Button();
            this.My_Account_Button = new System.Windows.Forms.Button();
            this.TextLogo = new System.Windows.Forms.PictureBox();
            this.ImageLogo = new System.Windows.Forms.PictureBox();
            this.Logged_Info_Label = new System.Windows.Forms.Label();
            this.Logout_Button = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.TextLogo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ImageLogo)).BeginInit();
            this.SuspendLayout();
            // 
            // Rooms_Button
            // 
            this.Rooms_Button.Location = new System.Drawing.Point(480, 269);
            this.Rooms_Button.Name = "Rooms_Button";
            this.Rooms_Button.Size = new System.Drawing.Size(275, 91);
            this.Rooms_Button.TabIndex = 1;
            this.Rooms_Button.Text = "Rooms";
            this.Rooms_Button.UseVisualStyleBackColor = true;
            this.Rooms_Button.Click += new System.EventHandler(this.button1_Click);
            // 
            // High_Score_Button
            // 
            this.High_Score_Button.Location = new System.Drawing.Point(480, 366);
            this.High_Score_Button.Name = "High_Score_Button";
            this.High_Score_Button.Size = new System.Drawing.Size(275, 96);
            this.High_Score_Button.TabIndex = 2;
            this.High_Score_Button.Text = "High Scores";
            this.High_Score_Button.UseVisualStyleBackColor = true;
            this.High_Score_Button.Click += new System.EventHandler(this.button2_Click_1);
            // 
            // My_Account_Button
            // 
            this.My_Account_Button.Location = new System.Drawing.Point(480, 468);
            this.My_Account_Button.Name = "My_Account_Button";
            this.My_Account_Button.Size = new System.Drawing.Size(275, 96);
            this.My_Account_Button.TabIndex = 3;
            this.My_Account_Button.Text = "My Account";
            this.My_Account_Button.UseVisualStyleBackColor = true;
            this.My_Account_Button.Click += new System.EventHandler(this.button3_Click);
            // 
            // TextLogo
            // 
            this.TextLogo.Image = global::GUI.Properties.Resources.text_logo;
            this.TextLogo.Location = new System.Drawing.Point(408, 110);
            this.TextLogo.Name = "TextLogo";
            this.TextLogo.Size = new System.Drawing.Size(420, 153);
            this.TextLogo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.TextLogo.TabIndex = 6;
            this.TextLogo.TabStop = false;
            // 
            // ImageLogo
            // 
            this.ImageLogo.Image = global::GUI.Properties.Resources.logo;
            this.ImageLogo.Location = new System.Drawing.Point(44, 12);
            this.ImageLogo.Name = "ImageLogo";
            this.ImageLogo.Size = new System.Drawing.Size(129, 114);
            this.ImageLogo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.ImageLogo.TabIndex = 5;
            this.ImageLogo.TabStop = false;
            // 
            // Logged_Info_Label
            // 
            this.Logged_Info_Label.AutoSize = true;
            this.Logged_Info_Label.Location = new System.Drawing.Point(12, 544);
            this.Logged_Info_Label.Name = "Logged_Info_Label";
            this.Logged_Info_Label.Size = new System.Drawing.Size(100, 20);
            this.Logged_Info_Label.TabIndex = 7;
            this.Logged_Info_Label.Text = "Logged in as";
            this.Logged_Info_Label.Click += new System.EventHandler(this.label1_Click);
            // 
            // Logout_Button
            // 
            this.Logout_Button.Location = new System.Drawing.Point(1091, 27);
            this.Logout_Button.Name = "Logout_Button";
            this.Logout_Button.Size = new System.Drawing.Size(136, 55);
            this.Logout_Button.TabIndex = 4;
            this.Logout_Button.Text = "Log Out";
            this.Logout_Button.UseVisualStyleBackColor = true;
            this.Logout_Button.Click += new System.EventHandler(this.button4_Click);
            // 
            // MainMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1231, 622);
            this.Controls.Add(this.Logged_Info_Label);
            this.Controls.Add(this.ImageLogo);
            this.Controls.Add(this.Logout_Button);
            this.Controls.Add(this.My_Account_Button);
            this.Controls.Add(this.High_Score_Button);
            this.Controls.Add(this.Rooms_Button);
            this.Controls.Add(this.TextLogo);
            this.Name = "MainMenu";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "FullStaki";
            this.Load += new System.EventHandler(this.MainMenu_Load);
            ((System.ComponentModel.ISupportInitialize)(this.TextLogo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ImageLogo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button Rooms_Button;
        private System.Windows.Forms.Button High_Score_Button;
        private System.Windows.Forms.Button My_Account_Button;
        private System.Windows.Forms.PictureBox ImageLogo;
        private System.Windows.Forms.PictureBox TextLogo;
        private System.Windows.Forms.Label Logged_Info_Label;
        private System.Windows.Forms.Button Logout_Button;
    }
}