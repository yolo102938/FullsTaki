using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel.Design;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Windows.Forms;
using TakiClient;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Diagnostics;
using Newtonsoft.Json;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.StartPanel;

namespace GUI.Forms
{
    
    public partial class GameRoom : Form
    {

        //true means you need to update it
        public class Diffrence
        {
            public bool CardImages = false;
            public bool firstPlayer = false;
            public bool secondPlayer = false;
            public bool thirdPlayer = false;
            public bool card_bank = false;
            public int card_bank_dec = 0;
        }
        public class ServerResponse
        {

            public List<Image> CardImages = new List<Image>();
            public List<PlayerInfo> Players = new List<PlayerInfo>();
            public string turn;
            public Image placed_card;
            public override bool Equals(object obj)
            {
                if (obj == null) return false;
                if (!(obj is ServerResponse)) return false;
                ServerResponse tempResp = (ServerResponse)obj;
                Diffrence temp = new Diffrence();
                this.Diffrentiate(tempResp, temp);

                return ((temp.card_bank && temp.CardImages && temp.firstPlayer && temp.secondPlayer && temp.thirdPlayer &&temp.thirdPlayer));

            }
            //function will tell whats the diffrence between last resp and this one to make updating smoother
            public Diffrence Diffrentiate(ServerResponse tempResp, Diffrence ret)
            {
                //Diffrence ret = new Diffrence();
                //oppoments checker
                bool temp = false;
                for (int i =0; i < this.Players.Count; i++)
                {
                    temp = !(tempResp.Players[i].Equals(Players[i]));
                    if (temp)
                    {
                        ret.card_bank = tempResp.Players[i].cardCount > this.Players[i].cardCount;
                        ret.card_bank_dec = tempResp.Players[i].cardCount - this.Players[i].cardCount; i++;
                    }
                    switch (i)
                    {
                        case 0:
                            ret.firstPlayer = temp;
                            break;
                        case 1:
                            ret.secondPlayer = temp;
                            break;
                        case 2:
                            ret.thirdPlayer = temp;
                            break;
                    }
                    
                }
                bool cur = true;
                for (int i = 0;i< tempResp.CardImages.Count;i++) 
                {
                    try {
                        bool start = !cur;
                        cur = cur && (string)this.CardImages[i].Tag == (string)tempResp.CardImages[i].Tag;
                    }
                    catch
                    {
                        cur = false; break;
                    }
                    
                }
                //Debug.WriteLine("this: " + this.CardImages.Count + " tempResp:" + tempResp.CardImages.Count);
                ret.CardImages = cur && this.CardImages.Count == tempResp.CardImages.Count;
                ret.CardImages = !ret.CardImages;
                return ret;
            }
        }
        public ServerResponse call_server()
        {
            ServerResponse response = new ServerResponse();
            string getrooms = TakiProtocol.GetCurrentGameState();

            TakiClient.Socket.SendMsg(getrooms);
            //MSG p1 = TakiClient.Socket.RecvMsg();
            //Console.WriteLine(Socket.LoggedUser + " --> " + p1.code + " --> " + p1.json.ToString());
            MSG msg = TakiClient.Socket.RecvMsg();
            Console.WriteLine(Socket.LoggedUser + " --> " + msg.code + " --> " + msg.json.ToString());
            while (msg.code != (int)TakiResponse.GET_GAME_STATE)
            {
                msg = TakiClient.Socket.RecvMsg();
                Console.WriteLine(Socket.LoggedUser + " --> " + msg.code + " --> " + msg.json.ToString());
            }
            //(p1.code == 112 || p1.code == 113)
            if ( msg != null && msg.code == (int)TakiResponse.GET_GAME_STATE)
            {
                ///string msg = Socket.RecvMsgByResponse((int)TakiResponse.GET_GAME_STATE);
                Console.WriteLine("k");
                JArray jsonArray = (JArray)JObject.Parse(msg.json)["players"];
                response.Players = new List<PlayerInfo>();
                try
                {
                    foreach (JObject obj in jsonArray)
                    {
                        response.Players.Add(new PlayerInfo { Name = obj.Value<string>("name"), cardCount = obj.Value<int>("card_count") });
                    }
                }
                catch { MessageBox.Show(msg.json); }


                //Client cards

                jsonArray = (JArray)JObject.Parse(msg.json)["cards"];
                var imgs = new List<Image>();
                foreach (JObject obj in jsonArray)
                {
                    string color = obj.Value<string>("color");
                    string what = obj.Value<string>("what");
                    Image cardImage;
                    cardImage = (Bitmap)global::GUI.Properties.Resources.ResourceManager.GetObject($"{color}_{what}");
                    cardImage.Tag = (color + what);
                    response.CardImages.Add((cardImage));

                }

                //Current player

                response.turn = JObject.Parse(msg.json)["turn"].ToString();

                //Last Card

                {
                    var obj = JObject.Parse(msg.json)["placed_card"];
                    string color = obj.Value<string>("color");
                    string what = obj.Value<string>("what");
                    //MessageBox.Show(color + what);
                    if (color == "none")
                    {
                        response.placed_card = ((Bitmap)global::GUI.Properties.Resources.Empty);
                        response.placed_card.Tag = (color + what);
                    }
                    else
                    {
                        response.placed_card = ((Bitmap)global::GUI.Properties.Resources.ResourceManager.GetObject($"{color}_{what}"));
                        response.placed_card.Tag = (color + what);
                    }

                }
                return response;
            }
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
            public override bool Equals(Object obj)
            {
                if ((obj == null) || !this.GetType().Equals(obj.GetType()))
                {
                    return false;
                }
                else
                {
                    PlayerInfo temp = (PlayerInfo)obj;
                    return (temp.Name==this.Name&&temp.cardCount == this.cardCount);
                }
            }
            public override int GetHashCode()
            {
                unchecked
                {
                    int hash = 17;
                    hash = hash * 23 + (Name != null ? Name.GetHashCode() : 0);
                    hash = hash * 23 + cardCount.GetHashCode();
                    return hash;
                }
            }

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

        public GameRoom(int playerCount = 2)
        {
            Text += Socket.LoggedUserFormatted;
            InitializeComponent(playerCount);
            createEmpty();
            resp = call_server();
            CreateCardBank(deck_count);
            diff = new Diffrence { CardImages = true, firstPlayer = true, secondPlayer = true, thirdPlayer = false, card_bank = false };
            InitializeGameRoom();

            DiscardCard_Click(null,null);

            timer = new Timer();
            timer.Interval = 300; 
            timer.Tick += Timer_Tick;
            timer.Start();

            //InitializeGameRoom();

        }
        private void Timer_Tick(object sender, EventArgs e)
        {
            ServerResponse tempResp = call_server();
            //if nothing changed, no need to update stuff.
            if (!resp.Equals(tempResp))
            {
                diff = new Diffrence();
                diff = resp.Diffrentiate(tempResp,diff);
                resp = tempResp;
                
                InitializeGameRoom();
            }
            {
            }
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
            playedcardsList.Add(new EnemyCard
            {
                Image = resized_Image,
                Location = new Point(tempX_, tempY_)
            });
            this.Controls.Add(temp);

        }
        private void InitializeGameRoom()
        {
            currentPlayer = resp.turn;
            cardImages = resp.CardImages;
            playedCardStack.Add(resp.placed_card);

            // Create the player's cards

            CreatePlayerCards();
            
            
            CreateOpponentCards(resp.Players.Count);

            // Create the card piles
            CreateCardPiles();

            // Initialize current player
            
            this.Refresh();

        }


        private void CreatePlayerCards()
        {
            if (!diff.CardImages) { return; }
            // Clear previous player's cards
            foreach (var card in playerCardsList)
            {
                this.Controls.Remove(card.Picture);

            }
            playerCardsList.Clear();
            this.Refresh();
            int startLocationX = this.Width / 2 - ((resp.CardImages.Count * 40) / 2);

            for (int i = 0; i < resp.CardImages.Count; i++)
            {
                Image resizedImage = resp.CardImages[i].GetThumbnailImage(70, 100, null, IntPtr.Zero);
                resizedImage.Tag = resp.CardImages[i].Tag;
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
                selectedCard = card;
            }
            playerNames["You"] = new PlayerName { Location = new Point(startLocationX + (resp.CardImages.Count * 30) / 2, this.Height - 150), rotate = 0 };

        }

        private void CreateOpponentCards(int playerCount)
        {

            PictureBox[][] tempOpponentCards = new PictureBox[playerCount][];

            for (int p = 0; p < playerCount; p++)
            {
                if (opponentCards == null)
                {
                    opponentCards= new PictureBox[playerCount][];
                }
                bool change = false;
                tempOpponentCards[p] = new PictureBox[resp.Players[p].cardCount];

                int startLocationX;
                int startLocationY;
                bool rotate;

                switch (p)
                {
                    case 0: // Opponent 1 (top)
                        change = diff.firstPlayer;
                        startLocationX = this.Width / 2 - ((resp.Players[p].cardCount * 30) / 2);
                        startLocationY = 30;
                        rotate = false;
                        playerNames[resp.Players[p].Name] = new PlayerName { Location = new Point(startLocationX+(resp.Players[p].cardCount * 30) /2, startLocationY+100) ,rotate = 0}; //later in backend add names
                        break;
                    case 1: // Opponent 2 (left)
                        change = diff.secondPlayer;
                        startLocationX = 30;
                        startLocationY = this.Height / 2 - ((cardImages.Count * 30) / 2);
                        rotate = true;
                        playerNames[resp.Players[p].Name] = new PlayerName { Location = new Point(startLocationX+150, startLocationY+(resp.Players[p].cardCount * 30)/2), rotate = 1 }; //later in backend add names
                        break;
                    case 2: // Opponent 3 (right)
                        change = diff.thirdPlayer;
                        startLocationX = this.Width - 80;
                        startLocationY = this.Height / 2 - ((cardImages.Count * 30) / 2);
                        rotate = true;
                        playerNames[resp.Players[p].Name] = new PlayerName { Location = new Point(startLocationX-100,startLocationY +(resp.Players[p].cardCount *30) / 2),rotate =-1 };
                        break;
                    default:
                        throw new Exception("Unsupported player count");
                }
                if (true)
                {
                    for (int i = 0; i < tempOpponentCards[p].Length; i++)
                    {
                        Image cardImage = global::GUI.Properties.Resources.Deck;
                        Image resizedImage = cardImage.GetThumbnailImage(70, 100, null, IntPtr.Zero);

                        if (rotate)
                        {
                            resizedImage.RotateFlip(RotateFlipType.Rotate90FlipNone);
                            tempOpponentCards[p][i] = new PictureBox
                            {
                                Size = new Size(70, 100),
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
                            tempOpponentCards[p][i] = new PictureBox
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
                    }
                    opponentCards[p] = new PictureBox[resp.Players[p].cardCount];
                    if (change)
                    {
                        this.Refresh();
                    }
                    for(int i = 0; i < tempOpponentCards[p].Length; i++)
                    {
                        opponentCards[p][i] = tempOpponentCards[p][i];
                    }
                    if (change)
                    {
                        this.Refresh();
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


            var second_playedCardStack = new PictureBox();
            
            int LocationX = this.Width / 2 -120;
            int LocationY = this.Height / 2-50 ;
            var rand = new Random();
            int tempX = LocationX + rand.Next(-5, 5);
            int tempY = LocationY + rand.Next(-3, 3);

           
                if (playedCardStack.Count == 0)
                {
                    return;
                }
                /*if (playedCardStack.Count > 20)
                {
                    i = playedCardStack.Count - 20;
                }*/
                Image resizedImage = playedCardStack.Last().GetThumbnailImage(70, 100, null, IntPtr.Zero);
                resizedImage = (Image)RotateImage((Bitmap)resizedImage, rand.Next(-20, 20));
                tempX = LocationX + rand.Next(-5, 5);
                tempY = LocationY + rand.Next(-3, 3);
                second_playedCardStack = new PictureBox
                {
                    Size = new Size(70, 100),
                    Location = new Point(tempX,tempY),
                    Image = resizedImage,
                    BackColor = Color.Transparent
                };
                    playedcardsList.Add(new EnemyCard
                {
                    Image = resizedImage,
                    Location = new Point(tempX,tempY)
                });




            

        }
        private void CreateCardBank(int amount) //creates a pile in the right middle with all the unused cards, rn random until backend
        {
            var rand = new Random();
            int space = 0;
            try {
                    space = rand.Next(10, 200 / amount); 
            }
            catch(Exception e) 
            {
                space = rand.Next( 150 / amount,10); 
            }
            int LocationX = this.Width / 2 +50+space*amount;
            int LocationY = this.Height / 2 - 50;
            for (int i = 0; i < amount; i++)
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
                CardsDeckList.Add(card);
            }
        }
        private void CreateCardPiles()
        {
            if (!diff.card_bank && (diff.firstPlayer || diff.secondPlayer || diff.thirdPlayer || diff.CardImages) && ((string)resp.placed_card.Tag).ToCharArray()[0] != 'n' && ((string)resp.placed_card.Tag).ToCharArray()[0] != 'N')
            {
                playedCardStack.Add(resp.placed_card);
                CreatePlayedCards();
            }
            if (diff.card_bank)
            {
                for(int i = 0; i < diff.card_bank_dec; i++)
                {
                    CardBank_Click(true);
                }
            }
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

            /*foreach (var card in cardsList)
            {
                e.Graphics.DrawImage(card.Image, card.Location);
            }*/
            foreach (var card in playedcardsList)
            {
                e.Graphics.DrawImage(card.Image, card.Location);
            }
            foreach (var cards in opponentCards)
            {
                foreach (var card in cards)
                {
                    e.Graphics.DrawImage(card.Image, card.Location);
                }
            }

            foreach (var card in cardBank)
            {
                e.Graphics.DrawImage(card.Image, card.Location);
            }
            foreach (var card in playerCardsList)
            {
                e.Graphics.DrawImage(card.Image, card.Location);
            }
            foreach (var card in CardsDeckList)
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
                    string tem = selectedCard.Image.Tag as string;
                    Dictionary<string, string> jsonDictionary = new Dictionary<string, string>
                    {
                        { "picture_tag",tem }
                    };
                    
                    TakiMessage loginMessage = new TakiMessage
                    {
                        Code = (int)TakiRequest.PLAY_CARD,
                        Content = JsonConvert.SerializeObject(jsonDictionary)
                    };
                    
                    TakiClient.Socket.SendMsg(loginMessage.ToString());
                    MSG msg = TakiClient.Socket.RecvMsg();

                    //string status = JObject.Parse(msg.json)["status"].ToString(); ;

                    if (msg.code == (int)TakiResponse.PLAY_CARD_ANSWER)
                    {
                        int ind = 0;
                        //not sure if even needed, when u do it serverResp will be with updated cards
                        foreach(ClickableCard img in playerCardsList)
                        {

                            if(img.Image.Equals(selectedCard.Image))
                            {
                           
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
        private void CardBank_Click(bool allow = false)
        {
            bool serverAllow = false;
            if (!allow)
            {
                TakiMessage getrooms = new TakiMessage
                {
                    Code = (int)TakiRequest.CARD_BANK_PREMISION,
                    Content = ""
                };

                TakiClient.Socket.SendMsg(getrooms.ToString());
                MSG msg = TakiClient.Socket.RecvMsg();
                serverAllow = msg.code == 100;

            }
            if (allow||serverAllow)
            {
                this.Controls.Remove(cardBank.First().Picture);
                cardBank.Remove(cardBank.First());
                deck_count--;
                CardsDeckList.Remove(CardsDeckList.First());
                if (deck_count== 0)
                {
                    foreach(var remaining in cardBank)
                    {
                        this.Controls.Remove(remaining.Picture);
                    }
                    
                    cardBank.Clear();
                    CardsDeckList.Clear();
                    this.Refresh();
                    deck_count = rand.Next(5,10);
                    CreateCardBank(deck_count);
                }
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
