using System;
using System.Collections.Generic;
using System.ComponentModel.Design;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Windows.Forms;

namespace GUI.Forms
{

    public partial class GameRoom : Form
    {

        public class ServerResponse
        {
            public List<Image> CardImages { get; set; }
            public List<PlayerInfo> Players { get; set; }
            public string turn;
            public Image placed_card;
        }
        public ServerResponse call_server()
        {
            ServerResponse response = new ServerResponse();

            // Replace this with actual server call later


            response.CardImages = new List<Image>() { (Bitmap)global::GUI.Properties.Resources.ResourceManager.GetObject($"Blue_4"), (Bitmap)global::GUI.Properties.Resources.ResourceManager.GetObject($"Blue_2"),(Bitmap)global::GUI.Properties.Resources.ResourceManager.GetObject($"Green_7") };
            response.Players = new List<PlayerInfo>() { new PlayerInfo{ Name = "David", cardCount = 2 }, new PlayerInfo{ Name = "Thomas" ,cardCount = 5} };
            response.turn = "You";
            response.placed_card = (Bitmap)global::GUI.Properties.Resources.ResourceManager.GetObject($"Blue_3");
            return response;
        }

        public class EnemyCard
            {
                public Image Image { get; set; }
                public Point Location { get; set; }
            }
        public class PlayerInfo
        {
            public string Name { get; set; }
            public int cardCount { get; set; } = 0;
        }
        public class PlayerName
        {
            public Point Location { get; set; }
            public int rotate { get; set; } // 0 no rotation, 1 90 degrees, -1 -90 degrees
        }
        class ClickableCard //diffrent because of selected cards, basically any card that needs to be clicked.
            {
                public Image Image { get; set; }
                public Point Location { get; set; }
                public PictureBox Picture { get; set; }
            }


        // Update the create methods to add Card objects to the cards list




        private Random rand = new Random();
        private List<Image> cardImages;
        private string[] colors = { "Red", "Blue", "Yellow", "Green" };

        public GameRoom(int playerCount = 3)
        {
           

            InitializeComponent(playerCount);
            createEmpty();
            InitializeGameRoom(playerCount);

        }
        public void createEmpty()
        {

            this.DoubleBuffered = true;  // enable double buffering to prevent flickering
            this.MouseClick += this.DiscardCard_Click;
            int tempX_ = this.Width / 2 - 120;
            int tempY_ = this.Height / 2 - 100;
            var ra_nd = new Random();
            Image resized_Image = global::GUI.Properties.Resources.Empty.GetThumbnailImage(150, 150, null, IntPtr.Zero);

            PictureBox temp = new PictureBox
            {
                Size = new Size(150, 150),
                Location = new Point(tempX_, tempY_),
                Image = resized_Image,
                BackColor = Color.Transparent
            };
            temp.Click += (s, e) => this.PlayedCard_Click(); // Add click event to each card
            cardsList.Add(new EnemyCard
            {
                Image = resized_Image,
                Location = new Point(tempX_, tempY_)
            });
            this.Controls.Add(temp);

        }
        private void InitializeGameRoom(int playerCount)
        {
            resp = call_server();

            // Initialize random card images
            cardImages = resp.CardImages;
            playedCardStack.Add(resp.placed_card);
            // Create the player's cards
            CreatePlayerCards();

            // Create the opponent's cards
            CreateOpponentCards(resp.Players.Count);

            // Create the card piles
            CreateCardPiles();

            // Initialize current player
            currentPlayer = "You";
        }

        private List<Image> GetRandomCardImages()
        {
            int numCards = rand.Next(1, 15);
            List<Image> cardImages = new List<Image>();

            if (numCards == 0)
            {
                Image cardImage;
                cardImage = (Bitmap)global::GUI.Properties.Resources.crown;
                cardImages.Add(cardImage);
            }

            for (int i = 0; i < numCards; i++)
            {
                string cardColor = colors[rand.Next(colors.Length)];
                int cardNumber = rand.Next(0, 10);
                Image cardImage;
                cardImage = (Bitmap)global::GUI.Properties.Resources.ResourceManager.GetObject($"{cardColor}_{cardNumber}");
                cardImages.Add(cardImage);
            }

            return cardImages;
        }


        private void CreatePlayerCards()
        {
          
            // Clear previous player's cards
            foreach (var card in playerCardsList)
            {
                this.Controls.Remove(card.Picture);

            }
            playerCardsList.Clear();
            this.Refresh();
            int startLocationX = this.Width / 2 - ((cardImages.Count * 40) / 2);

            for (int i = 0; i < cardImages.Count; i++)
            {
                Image resizedImage = cardImages[i].GetThumbnailImage(70, 100, null, IntPtr.Zero);

                var card = new ClickableCard
                {
                    Image = resizedImage,
                    Location = new Point(startLocationX + (i * 40), this.Height - 100),
                    Picture = new PictureBox
                    {
                        Size = new Size(70, 100),
                        Location = new Point(startLocationX + (i * 40), this.Height - 100),
                        Image = resizedImage,
                        BackColor = Color.Transparent
                    }
                };
                card.Picture.Click += (s, e) => this.Card_Click(card); // Add click event to each card
                playerCardsList.Add(card);
                this.Controls.Add(card.Picture);
            }
            playerNames["You"] = new PlayerName { Location = new Point(startLocationX + (cardImages.Count * 30) / 2, this.Height - 150), rotate = 0 };
        }

        private void CreateOpponentCards(int playerCount)
        {

            opponentCards = new PictureBox[playerCount][];

            for (int p = 0; p < playerCount; p++)
            {
                List<Image> cardImages = GetRandomCardImages();
                opponentCards[p] = new PictureBox[resp.Players[p].cardCount];

                int startLocationX;
                int startLocationY;
                bool rotate;

                switch (p)
                {
                    case 0: // Opponent 1 (top)
                        
                        startLocationX = this.Width / 2 - ((resp.Players[p].cardCount * 30) / 2);
                        startLocationY = 30;
                        rotate = false;
                        playerNames[resp.Players[p].Name] = new PlayerName { Location = new Point(startLocationX+(resp.Players[p].cardCount * 30) /2, startLocationY+100) ,rotate = 0}; //later in backend add names
                        break;
                    case 1: // Opponent 2 (left)
                        startLocationX = 30;
                        startLocationY = this.Height / 2 - ((cardImages.Count * 30) / 2);
                        rotate = true;
                        playerNames[resp.Players[p].Name] = new PlayerName { Location = new Point(startLocationX+150, startLocationY+(resp.Players[p].cardCount * 30)/2), rotate = 1 }; //later in backend add names
                        break;
                    case 2: // Opponent 3 (right)
                        startLocationX = this.Width - 80;
                        startLocationY = this.Height / 2 - ((cardImages.Count * 30) / 2);
                        rotate = true;
                        playerNames[resp.Players[p].Name] = new PlayerName { Location = new Point(startLocationX-100,startLocationY +(resp.Players[p].cardCount *30) / 2),rotate =-1 };
                        break;
                    default:
                        throw new Exception("Unsupported player count");
                }

                for (int i = 0; i < opponentCards[p].Length; i++)
                {
                    Image cardImage = global::GUI.Properties.Resources.Deck;
                    Image resizedImage = cardImage.GetThumbnailImage(70, 100, null, IntPtr.Zero);

                    if (rotate)
                    {
                        resizedImage.RotateFlip(RotateFlipType.Rotate90FlipNone);
                        opponentCards[p][i] = new PictureBox
                        {
                            Size = new Size(70,100),
                            Location = new Point(startLocationX, startLocationY + (i * 30)),
                            Image = resizedImage,
                            BackColor = Color.Transparent
                        };
                        cardsList.Add(new EnemyCard
                        {
                            Image = resizedImage,
                            Location = new Point(startLocationX, startLocationY + (i * 30))
                        });
                    }
                    else
                    {
                        opponentCards[p][i] = new PictureBox
                        {
                            Size = new Size(70, 100),
                            Location = new Point(startLocationX + (i * 30), startLocationY),
                            Image = resizedImage,
                            BackColor = Color.Transparent
                        };
                        cardsList.Add(new EnemyCard
                        {
                            Image = resizedImage,
                            Location = new Point(startLocationX + (i * 30), startLocationY)
                        });
                    }


                    //this.Controls.Add(opponentCards[p][i]);
                }
            }
        }
        //from https://stackoverflow.com/questions/12024406/how-can-i-rotate-an-image-by-any-degree
        ///, used to rotate an image by n degrees for played cards stack
        private Bitmap RotateImage(Bitmap bmp, float angle)
        {
            float height = bmp.Height;
            float width = bmp.Width;
            int hypotenuse = System.Convert.ToInt32(System.Math.Floor(Math.Sqrt(height * height + width * width)));
            Bitmap rotatedImage = new Bitmap(hypotenuse, hypotenuse);
            using (Graphics g = Graphics.FromImage(rotatedImage))
            {
                g.TranslateTransform((float)rotatedImage.Width / 2, (float)rotatedImage.Height / 2); //set the rotation point as the center into the matrix
                g.RotateTransform(angle); //rotate
                g.TranslateTransform(-(float)rotatedImage.Width / 2, -(float)rotatedImage.Height / 2); //restore rotation point into the matrix
                g.DrawImage(bmp, (hypotenuse - width) / 2, (hypotenuse - height) / 2, width, height);
            }
            return rotatedImage;
        }
        private void CreatePlayedCards() //creates a pile in the middle with all the recently played card, rn random until backend
        {


            var second_playedCardStack = new PictureBox[1];
            
            int LocationX = this.Width / 2 -120;
            int LocationY = this.Height / 2-50 ;
            var rand = new Random();
            int tempX = LocationX + rand.Next(-5, 5);
            int tempY = LocationY + rand.Next(-3, 3);

            for (int i = 0; i < 1; i++)
            {
                if (playedCardStack.Count == 0)
                {
                    break;
                }
                if (playedCardStack.Count > 20)
                {
                    i = 19;
                }
                Image resizedImage = playedCardStack.Last().GetThumbnailImage(70, 100, null, IntPtr.Zero);
                resizedImage = (Image)RotateImage((Bitmap)resizedImage, rand.Next(-20, 20));
                tempX = LocationX + rand.Next(-5, 5);
                tempY = LocationY + rand.Next(-3, 3);
                second_playedCardStack[i] = new PictureBox
                {
                    Size = new Size(70, 100),
                    Location = new Point(tempX,tempY),
                    Image = resizedImage,
                    BackColor = Color.Transparent
                };
                    cardsList.Add(new EnemyCard
                {
                    Image = resizedImage,
                    Location = new Point(tempX,tempY)
                });




            }

        }
        private void CreateCardBank(int amount) //creates a pile in the right middle with all the unused cards, rn random until backend
        {

            List<Image> cardImages = GetRandomCardImages();


            var rand = new Random();
            int space = 0;
            try {
                    space = rand.Next(10, 200 / amount); 
            }
            catch(Exception e) 
            {
                space = rand.Next( 200 / amount,10); 
            }
            int LocationX = this.Width / 2 +space*amount;
            int LocationY = this.Height / 2 - 50;
            for (int i = 0; i < cardImages.Count; i++)
            {
                Image cardImage = global::GUI.Properties.Resources.Deck;
                Image resizedImage = cardImage.GetThumbnailImage(70, 100, null, IntPtr.Zero);
                
                var card = new ClickableCard
                {
                    Image = global::GUI.Properties.Resources.Empty.GetThumbnailImage(70, 100, null, IntPtr.Zero),
                    Location = new Point(LocationX+space*i,LocationY),
                    Picture = new PictureBox
                        {
                            Size = new Size(70, 100),
                            Location = new Point(LocationX - space * i, LocationY),
                            Image = resizedImage,
                            BackColor = Color.Transparent
                        }
                };
                cardBank.Add(card);
                this.Controls.Add(card.Picture);
                card.Picture.Click += (s, e) => this.CardBank_Click(); // Add click event to each card
                playerCardsList.Add(card);
                


            }
        }
        private void CreateCardPiles()
        {
            var rand = new Random();

            CreatePlayedCards();
            CreateCardBank(20);
        }


        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            foreach (var player in playerNames)
            {
                using (SolidBrush brush = new SolidBrush(player.Key == currentPlayer ? Color.Red : Color.Black))
                {
                    e.Graphics.TranslateTransform(player.Value.Location.X, player.Value.Location.Y);
                    e.Graphics.RotateTransform(player.Value.rotate * 90);
                    Font boldFont = new Font(this.Font.FontFamily, this.Font.Size * 1.5f, FontStyle.Bold);

                    e.Graphics.DrawString(player.Key, boldFont, brush, new Point(0, 0));
                    e.Graphics.ResetTransform();
                }
            }

            foreach (var card in cardsList)
            {
                e.Graphics.DrawImage(card.Image, card.Location);
            }
            foreach (var card in cardBank)
            {
                e.Graphics.DrawImage(card.Image, card.Location);
            }
            foreach (var card in playerCardsList)
            {
                e.Graphics.DrawImage(card.Image, card.Location);
            }
        }
        // The event when a card is clicked
        private void Card_Click(ClickableCard card)
        {


            if (selectedCard != null)
            {

                // Restore previous selected card
                selectedCard.Picture.Location = selectedCard.Location;
                selectedCard.Picture.Size = new Size(70, 100);

            }

            // Select new card
            selectedCard = card;
            selectedCard.Picture.Location = new Point(card.Location.X, card.Location.Y - 30); // Move card up
            // selectedCard.Picture.Size = new Size(90, 120); // Increase size
            //this.Refresh();
        }
        private void PlayedCard_Click()
        {

                if (selectedCard != null)
                {
                    if (true)//add if server allows after ohad finished
                    {
                    int ind = 0;
                    //not sure if even needed, when u do it serverResp will be with updated cards
                    foreach(ClickableCard img in playerCardsList)
                    {

                        if(img.Image.Equals(selectedCard.Image)) {
                           
                            cardImages.RemoveAt(ind);
                        }
                        ind++;
                       
                           
                        
                    }
                    this.playedCardStack.Add(selectedCard.Image);

                    CreatePlayedCards();
                    selectedCard.Picture.Location = selectedCard.Location;
                    selectedCard.Picture.Size = new Size(70, 100);
                    selectedCard = null;

                   this.Refresh();
                    
                    CreatePlayerCards();
                }
                    
                }
        }
        private void CardBank_Click()
        {
            if (true) 
            {
                this.Controls.Remove(cardBank.First().Picture);
                cardBank.Remove(cardBank.First());
                this.Refresh();
            }

        }


        // The event when the background is clicked
        private void DiscardCard_Click(object sender, MouseEventArgs e)
        {
            
            if (selectedCard != null)
            {

                // Deselect card
                selectedCard.Picture.Location = selectedCard.Location;
                selectedCard.Picture.Size = new Size(70, 100);
                selectedCard = null;


            }
        }
        private void DeckCardStack_Click(object sender, EventArgs e)
        {
            // Here you would handle the logic when a player clicks on the deck to draw a card.
            // For example, add a new card to the player's hand.
        }

        // Use these Load methods to set the initial state of the game, or to handle different game states
        private void GameRoom_Load(object sender, EventArgs e)
        {

        }

        private void GameRoom_Load_1(object sender, EventArgs e)
        {

        }

        private void GameRoom_Load_2(object sender, EventArgs e)
        {

        }

        private void GameRoom_Load_3(object sender, EventArgs e)
        {

        }
    }
}
