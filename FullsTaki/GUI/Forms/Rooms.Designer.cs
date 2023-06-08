using GUI.DataTypes;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace GUI.Forms
{
    partial class Rooms
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param .name="disposing<>true if managed resources should be disposed; otherwise, false.</param>
        /// 
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
            this.components = new System.ComponentModel.Container();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.RoomList = new System.Windows.Forms.ListBox();
            this.button1 = new System.Windows.Forms.Button();
            this.name_label = new System.Windows.Forms.Label();
            this.name_input = new System.Windows.Forms.TextBox();
            this.pass_label = new System.Windows.Forms.Label();
            this.pass_input = new System.Windows.Forms.TextBox();
            this.login_button = new System.Windows.Forms.Button();
            this.Logout_Button = new System.Windows.Forms.Button();
            this.roomsBindingSource = new System.Windows.Forms.BindingSource(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.roomsBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::GUI.Properties.Resources.logo_with_text;
            this.pictureBox1.Location = new System.Drawing.Point(17, 1);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(532, 139);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // RoomList
            // 
            this.RoomList.FormattingEnabled = true;
            this.RoomList.ItemHeight = 20;
            this.RoomList.Location = new System.Drawing.Point(17, 191);
            this.RoomList.Name = "RoomList";
            this.RoomList.Size = new System.Drawing.Size(885, 344);
            this.RoomList.TabIndex = 3;
            this.RoomList.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(17, 541);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(197, 47);
            this.button1.TabIndex = 4;
            this.button1.Text = "Join Selected";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // name_label
            // 
            this.name_label.Location = new System.Drawing.Point(978, 264);
            this.name_label.Name = "name_label";
            this.name_label.Size = new System.Drawing.Size(122, 19);
            this.name_label.TabIndex = 5;
            this.name_label.Text = "Room Name:";
            this.name_label.Click += new System.EventHandler(this.name_label_Click);
            // 
            // name_input
            // 
            this.name_input.Location = new System.Drawing.Point(943, 285);
            this.name_input.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.name_input.Name = "name_input";
            this.name_input.Size = new System.Drawing.Size(205, 26);
            this.name_input.TabIndex = 6;
            this.name_input.TextChanged += new System.EventHandler(this.name_input_TextChanged);
            // 
            // pass_label
            // 
            this.pass_label.Location = new System.Drawing.Point(956, 313);
            this.pass_label.Name = "pass_label";
            this.pass_label.Size = new System.Drawing.Size(192, 28);
            this.pass_label.TabIndex = 7;
            this.pass_label.Text = "Rest of the stuff ohad";
            // 
            // pass_input
            // 
            this.pass_input.Location = new System.Drawing.Point(943, 343);
            this.pass_input.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pass_input.Name = "pass_input";
            this.pass_input.PasswordChar = '*';
            this.pass_input.Size = new System.Drawing.Size(205, 26);
            this.pass_input.TabIndex = 8;
            // 
            // login_button
            // 
            this.login_button.Location = new System.Drawing.Point(943, 508);
            this.login_button.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.login_button.Name = "login_button";
            this.login_button.Size = new System.Drawing.Size(214, 70);
            this.login_button.TabIndex = 9;
            this.login_button.Text = "Create Room";
            this.login_button.Click += new System.EventHandler(this.login_button_Click);
            // 
            // Logout_Button
            // 
            this.Logout_Button.Location = new System.Drawing.Point(1053, 24);
            this.Logout_Button.Name = "Logout_Button";
            this.Logout_Button.Size = new System.Drawing.Size(136, 55);
            this.Logout_Button.TabIndex = 10;
            this.Logout_Button.Text = "Log Out";
            this.Logout_Button.UseVisualStyleBackColor = true;
            this.Logout_Button.Click += new System.EventHandler(this.Logout_Button_Click);
            // 
            // Rooms
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1231, 622);
            this.Controls.Add(this.Logout_Button);
            this.Controls.Add(this.name_label);
            this.Controls.Add(this.name_input);
            this.Controls.Add(this.pass_label);
            this.Controls.Add(this.pass_input);
            this.Controls.Add(this.login_button);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.RoomList);
            this.Controls.Add(this.pictureBox1);
            this.Name = "Rooms";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.roomsBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.ListBox RoomList;
        private System.Windows.Forms.BindingSource roomsBindingSource;
        private System.Windows.Forms.Button button1;
        private Room[] rooms;
        private System.Windows.Forms.Label name_label;
        private System.Windows.Forms.TextBox name_input;
        private System.Windows.Forms.Label pass_label;
        private System.Windows.Forms.TextBox pass_input;
        private System.Windows.Forms.Button login_button;
        private System.Windows.Forms.Button Logout_Button;
    }
}