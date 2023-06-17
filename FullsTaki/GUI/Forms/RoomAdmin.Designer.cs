using GUI.DataTypes;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace GUI.Forms
{
    partial class RoomAdmin
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
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.RoomAdminBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.RoomList = new System.Windows.Forms.ListBox();
            this.button1 = new System.Windows.Forms.Button();
            this.Logout_Button = new System.Windows.Forms.Button();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.button3 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.RoomAdminBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(952, 228);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(188, 23);
            this.label2.TabIndex = 13;
            this.label2.Text = "Kick a user";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(417, 204);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(52, 25);
            this.label3.TabIndex = 14;
            this.label3.Text = "Users";
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(17, 446);
            this.button2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(885, 70);
            this.button2.TabIndex = 16;
            this.button2.Text = "Start Game";
            this.button2.Click += new System.EventHandler(this.button2_Click);
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
            this.RoomList.Location = new System.Drawing.Point(17, 232);
            this.RoomList.Name = "RoomList";
            this.RoomList.Size = new System.Drawing.Size(885, 184);
            this.RoomList.TabIndex = 3;
            this.RoomList.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(943, 288);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(197, 47);
            this.button1.TabIndex = 4;
            this.button1.Text = "Kick Selected";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Logout_Button
            // 
            this.Logout_Button.Location = new System.Drawing.Point(1066, 12);
            this.Logout_Button.Name = "Logout_Button";
            this.Logout_Button.Size = new System.Drawing.Size(136, 55);
            this.Logout_Button.TabIndex = 10;
            this.Logout_Button.Text = "Log Out";
            this.Logout_Button.UseVisualStyleBackColor = true;
            this.Logout_Button.Click += new System.EventHandler(this.Logout_Button_Click);
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
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(943, 361);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(197, 55);
            this.button3.TabIndex = 17;
            this.button3.Text = "Close Room";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // RoomAdmin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1231, 622);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.Logout_Button);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.RoomList);
            this.Controls.Add(this.pictureBox1);
            this.Name = "RoomAdmin";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.RoomAdmin_Load);
            ((System.ComponentModel.ISupportInitialize)(this.RoomAdminBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.ListBox RoomList;
        private System.Windows.Forms.BindingSource RoomAdminBindingSource;
        private System.Windows.Forms.Button button1;
        private List<DataTypes.User> rooms;
        private System.Windows.Forms.Button Logout_Button;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.Button button2;
        private int index;
        private int room_id;
        private System.Windows.Forms.Button button3;
    }
}