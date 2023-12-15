using System;
using System.Net.Sockets;
using System.Text;

namespace Common
{
    public static class Utilities
    {
        /// <summary>
        /// Constructs a basic HTTP GET request string for the given URL.
        /// </summary>
        /// <param name="url">The URL to request.</param>
        /// <returns>A string representing the HTTP GET request.</returns>
        public static string ConstructHttpGetRequest(string url)
        {
            var uri = new Uri(url);
            var request = new StringBuilder();
            request.AppendLine($"GET {uri.AbsolutePath} HTTP/1.1");
            request.AppendLine($"Host: {uri.Host}");
            request.AppendLine("Connection: close");
            request.AppendLine(); // An empty line is important to denote the end of the header section
            return request.ToString();
        }

        /// <summary>
        /// Logs a message with a timestamp.
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Log(string message)
        {
            Console.WriteLine($"[{DateTime.Now:yyyy-MM-dd HH:mm:ss}] {message}");
        }

        /// <summary>
        /// Sends data asynchronously over a socket.
        /// </summary>
        /// <param name="socket">The socket to use for sending.</param>
        /// <param name="data">The data to send.</param>
        /// <returns>A Task representing the asynchronous operation.</returns>
        public static async Task SendAsync(Socket socket, byte[] data)
        {
            int offset = 0;
            int remaining = data.Length;

            while (remaining > 0)
            {
                int sent = await Task.Factory.FromAsync(
                    socket.BeginSend(data, offset, remaining, SocketFlags.None, null, socket),
                    socket.EndSend);
                offset += sent;
                remaining -= sent;
            }
        }

        /// <summary>
        /// Reads data asynchronously from a socket until the specified condition is met.
        /// </summary>
        /// <param name="socket">The socket to read from.</param>
        /// <param name="condition">The condition that stops the reading.</param>
        /// <returns>The received data as a byte array.</returns>
        public static async Task<byte[]> ReceiveAsync(Socket socket, Func<byte[], bool> condition)
        {
            var buffer = new byte[4096];
            var receivedData = new List<byte>();

            while (true)
            {
                int received = await Task.Factory.FromAsync(
                    socket.BeginReceive(buffer, 0, buffer.Length, SocketFlags.None, null, socket),
                    socket.EndReceive);

                if (received == 0)
                {
                    break; // Socket closed
                }

                receivedData.AddRange(buffer.Take(received));

                if (condition(receivedData.ToArray()))
                {
                    break;
                }
            }

            return receivedData.ToArray();
        }
    }
}
