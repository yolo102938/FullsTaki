using System;
using System.Configuration;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;
using GUI.Forms;
using GUI;
using System.Data.SqlTypes;

namespace TakiClient
{
    public class MSG
    {
        public int code;
        public string json;
        public MSG(int cod,string jso) {code= cod; json = jso; } 
    }
    public static class Socket
    {
        private static readonly TcpClient clientSocket = new TcpClient();

        public static bool IsLogged => LoggedUser != null;

        public static string LoggedUser { get; set; } = null;

        public static string LoggedUserFormatted => IsLogged ? $" (Logged as {LoggedUser})" : "";

        public static bool Connected { get; set; }

        public static Address ServerAddress { get; } = new TakiClient.Address("127.0.01", 888);
        public static TcpClient getSocket()
        {
            return clientSocket;
        }
        static Socket()
        {
            try
            {
                clientSocket.Connect(ServerAddress.IP, ServerAddress.PORT);
            }
            catch
            {
                Connected = false;
                return;
            }
            Connected = true;
        }

        public static bool SendMsg(string msg)
        {
            try
            {
                NetworkStream stream = clientSocket.GetStream();
                byte[] outStream = Encoding.ASCII.GetBytes(msg);

                stream.Write(outStream, 0, outStream.Length);
                stream.Flush();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            return true;
        }

        public static MSG RecvMsg()
        {
            try
            {
                byte[] buffer = new byte[4];

                NetworkStream stream = clientSocket.GetStream();

                stream.Read(buffer, 0, 4);
                if (BitConverter.IsLittleEndian)
                    Array.Reverse(buffer);
                int responseCode = BitConverter.ToInt32(buffer, 0);

                stream.Read(buffer, 0, 4);
                if (BitConverter.IsLittleEndian)
                    Array.Reverse(buffer);
                int responseLength = BitConverter.ToInt32(buffer, 0);

                buffer = new byte[responseLength];
                stream.Read(buffer, 0, responseLength);
                string jsonString = Encoding.UTF8.GetString(buffer);
                return new MSG(responseCode, jsonString);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Connection Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return new MSG(101, "{}");
            }
        }


        public static string RecvMsgByResponse(params int[] responseTypes)
        {
            MSG recvMsg;
            int response;

                recvMsg = RecvMsg();
                try
                {
                    response = recvMsg.code;
                    if (response == (int)TakiResponse.ERROR || !responseTypes.Contains(response))
                    {
                        MessageBox.Show( recvMsg.json, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return null;
                    }
                }
                catch(Exception e)
                {
                    return null;
                }
            

            return recvMsg.code.ToString()+recvMsg.json;
        }
    }
}
