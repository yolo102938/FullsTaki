using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web.Script.Serialization;

namespace GUI.Forms
{
    public class TakiMessage
    {
        private string content;

        public TakiMessage()
        {
            Code = default;
            Length = default;
            content = default;
        }
        public TakiMessage(string message)
        {
            Code = message[0];
            Length = message.Substring(1, 4);
            content = message.Substring(5);
        }

        public TakiMessage(int code, string content)
        {
            Code = code;
            Content = content;
        }


        public int Code { get; set; }

        public string Length { get; private set; }

        public string Content
        {
            get => content;
            set
            {
                content = value;
                Length = ByteArrayToHexString(BitConverter.GetBytes(content.Length).Reverse().ToArray());
            }
        }

        public override string ToString()
        {
            return Code.ToString("X").PadLeft(4) + Length + content;
        }

        public Dictionary<string, string> ToDict()
        {
            return JsonConvert.DeserializeObject<Dictionary<string, string>>(content);
        }

        public Dictionary<string, object> ToMultiDict()
        {
            content = content.Trim('\0');
            JavaScriptSerializer serializer = new JavaScriptSerializer();
            return (Dictionary<string, object>)serializer.Deserialize<object>(content);
        }

        public static string ByteArrayToHexString(byte[] ba)
        {
            StringBuilder hex = new StringBuilder(ba.Length * 2);
            foreach (byte b in ba)
                hex.AppendFormat("{0:x2}", b);
            return hex.ToString();
        }
    }
}
