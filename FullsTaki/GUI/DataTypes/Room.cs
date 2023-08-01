using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Xml.Linq;

namespace GUI.DataTypes
{
    internal class Room
    {
        //idk how structs work
        public string name { get; set; }
        public int id { get; set; }
        public int max_players { get; set; }
        public int player_count { get; set; }
        /* public Room(string name_,int id_,int max_players_,int player_count_) 
         { 
             name = name_;
             id = id_;
             max_players = max_players_;
             player_count = player_count_; 
         }
         public Room() { }*/
        public override string ToString()
        {
            return ("|"+ id.ToString().PadLeft(35).PadRight(70) + "|"+name.PadLeft(35).PadRight(70) + "|"+(player_count.ToString()+"\\"+max_players.ToString()).PadLeft(35).PadRight(70) + "|");
        }
    }
}
