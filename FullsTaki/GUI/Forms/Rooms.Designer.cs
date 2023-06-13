﻿using GUI.DataTypes;
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
            this.index = 0;
            this.components = new System.ComponentModel.Container();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.RoomList = new System.Windows.Forms.ListBox();
            this.button1 = new System.Windows.Forms.Button();
            this.name_label = new System.Windows.Forms.Label();
            this.name_input = new System.Windows.Forms.TextBox();
            this.Logout_Button = new System.Windows.Forms.Button();
            this.roomsBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.button2 = new System.Windows.Forms.Button();
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
            this.button1.Location = new System.Drawing.Point(943, 303);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(197, 47);
            this.button1.TabIndex = 4;
            this.button1.Text = "Join Selected";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // name_label
            // 
            this.name_label.Location = new System.Drawing.Point(942, 397);
            this.name_label.Name = "name_label";
            this.name_label.Size = new System.Drawing.Size(122, 19);
            this.name_label.TabIndex = 5;
            this.name_label.Text = "Room Name:";
            this.name_label.Click += new System.EventHandler(this.name_label_Click);
            // 
            // name_input
            // 
            this.name_input.Location = new System.Drawing.Point(943, 418);
            this.name_input.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.name_input.Name = "name_input";
            this.name_input.Size = new System.Drawing.Size(205, 26);
            this.name_input.TabIndex = 6;
            this.name_input.TextChanged += new System.EventHandler(this.name_input_TextChanged);
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
            // comboBox1
            // 
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "2",
            "3",
            "4",
            "5"});
            this.comboBox1.Location = new System.Drawing.Point(943, 477);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 28);
            this.comboBox1.TabIndex = 11;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(939, 446);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(192, 28);
            this.label1.TabIndex = 12;
            this.label1.Text = "Max player count:";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(969, 362);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(188, 23);
            this.label2.TabIndex = 13;
            this.label2.Text = "CREATE ROOM";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(969, 228);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(188, 23);
            this.label3.TabIndex = 14;
            this.label3.Text = "JOIN ROOM";
            // 
            // comboBox2
            // 
            this.comboBox2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Location = new System.Drawing.Point(943, 254);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(197, 28);
            this.comboBox2.TabIndex = 15;
            this.comboBox2.SelectedIndexChanged += new System.EventHandler(this.comboBox2_SelectedIndexChanged);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(934, 510);
            this.button2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(214, 70);
            this.button2.TabIndex = 16;
            this.button2.Text = "Create Room";
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // Rooms
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1231, 622);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.Logout_Button);
            this.Controls.Add(this.name_label);
            this.Controls.Add(this.name_input);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.RoomList);
            this.Controls.Add(this.pictureBox1);
            this.Name = "Rooms";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Rooms_Load);
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
        private List<Room> rooms;
        private System.Windows.Forms.Label name_label;
        private System.Windows.Forms.TextBox name_input;
        private System.Windows.Forms.Button Logout_Button;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.Button button2;
        private int index;
    }
}