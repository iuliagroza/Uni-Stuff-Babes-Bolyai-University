// A client sends pairs of numbers, transmitted as text and separated by whitespace, and receives and prints the server response

using System;
using System.Net;
using System.Net.Sockets;

class Client
{

    public static void Main(string[] args)
    {
        try
        {
            Console.Write("Server Name/IP=");
            string srvName = Console.ReadLine();
            IPHostEntry hostEntry = Dns.GetHostEntry(srvName);
            IPAddress srvIp = null;
            foreach (IPAddress ip in hostEntry.AddressList)
            {
                if(ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    srvIp = ip;
                }
            }

            Console.WriteLine("IP={0}", srvIp);
            Console.Write("Server port=");
            string srvPortStr = Console.ReadLine();
            int srvPort = int.Parse(srvPortStr);
            Socket conn = new Socket(SocketType.Stream, ProtocolType.Tcp);
            conn.Connect(srvIp, srvPort);

            while(true)
            {
                Console.WriteLine("Give 2 numbers, enter 0 for ending.");
                Console.Write("A=");
                string strA = Console.ReadLine();
                if(strA.Trim() == "0")
                {
                    break;
                }
                Console.Write("B=");
                string strB = Console.ReadLine();
                string toSendStr = strA + " " + strB + "\n";
                byte[] toSendBytes = System.Text.Encoding.UTF8.GetBytes(toSendStr);
                conn.Send(toSendBytes);
                byte[] recvBytes = new byte[2048];
                int retBytes = conn.Receive(recvBytes);
                string retString = System.Text.Encoding.UTF8.GetString(recvBytes, 0, retBytes);
                Console.WriteLine("Received: {0}", retString);
            }

            conn.Close();
        }
        catch (Exception ex)
        {
            Console.WriteLine("Exception caught: {0}", ex);
        }
    }

}
