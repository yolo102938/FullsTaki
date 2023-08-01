using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace GUI.Forms
{
    partial class GameRoom
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
        private void InitializeComponent(int playerCount)
        {
            this.SuspendLayout();
            // 
            // GameRoom
            // 
            this.BackgroundImage = global::GUI.Properties.Resources.logo;
            this.ClientSize = new System.Drawing.Size(1367, 526);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "GameRoom";
            this.Load += new System.EventHandler(this.GameRoom_Load_3);
            this.ResumeLayout(false);

        }
        Diffrence diff = new Diffrence();
        ServerResponse resp;
        private Timer timer;
        private int deck_count = 8;
        //alot of bs not orginized
        private PictureBox[] playerCards;
        private PictureBox[][] opponentCards;
        private List<Image> playedCardStack = new List<Image>();
        private PictureBox deckCardStack;
        private List<EnemyCard> cardsList = new List<EnemyCard>();
        private List<EnemyCard> playedcardsList = new List<EnemyCard>();
        private List<ClickableCard> playerCardsList = new List<ClickableCard>();
        private List<ClickableCard> CardsDeckList = new List<ClickableCard>();
        private Dictionary<string,PlayerName> playerNames = new Dictionary<string, PlayerName>();
        private string currentPlayer = "";
        private  ClickableCard selectedCard = null;
        private List<ClickableCard> cardBank = new List<ClickableCard>();
        int playerCount;
        #endregion
    }
}