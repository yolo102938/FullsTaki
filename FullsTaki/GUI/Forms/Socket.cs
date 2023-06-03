﻿using System;
using System.Configuration;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;
using GUI.Forms;

namespace TakiClient
{
    public static class Socket
    {
        private static readonly TcpClient clientSocket = new TcpClient();

        public static bool IsLogged => LoggedUser != null;

        public static string LoggedUser { get; set; } = null;

        public static string LoggedUserFormatted => IsLogged ? $" (Logged as {LoggedUser})" : "";

        public static bool Connected { get; set; }

        public static Address ServerAddress { get; } = new Address(ConfigurationManager.AppSettings["server_ip"], int.Parse(ConfigurationManager.AppSettings["port"]));

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

        public static string RecvMsg()
        {
            try
            {
                NetworkStream stream = clientSocket.GetStream();
                byte[] inStream = new byte[8192];

                stream.Read(inStream, 0, 8192);
                return Encoding.ASCII.GetString(inStream);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Connection Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return null;
            }
        }

        public static string RecvMsgByResponse(params int[] responseTypes)
        {
            string recvMsg;
            TakiMessage response;

            do
            {
                recvMsg = RecvMsg();
                response = new TakiMessage(recvMsg);
                if (response.Code == (int)TakiResponse.ERROR)
                {
                    MessageBox.Show(TakiProtocol.FormatResponseByMessage(recvMsg), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return null;
                }

            } while (!responseTypes.Contains(response.Code));

            return recvMsg;
        }
    }
}