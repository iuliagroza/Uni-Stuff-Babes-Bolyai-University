// A server that accepts pairs of numbers, transmitted as text and separated by whitespace, and sends back their sums

using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;

class Session {
    private Session(Socket conn) {
        _conn = conn;
        _buffer = new byte[10];
    }
    
    private async Task<char> ReadNextChar() {
        if(_pos >= _size) {
            _pos = 0;
            _size = await Receive(_conn, _buffer, 0, _buffer.Length);
            if(_size == 0) {
                return '\0';
            }
        }
        byte b = _buffer[_pos];
        ++_pos;
        char c = (char)b;
        if(c == '\n' || c == '\r' || c == '\t') {
            c = ' ';
        } else if(c != ' ' && (c<'0' || c>'9')) {
            Console.WriteLine("Unexpected caracter: {0}", c);
            c = ' ';
        }
        return c;
    }

    private async Task Run() {
        _pos = 0;
        _size = await Receive(_conn, _buffer, 0, _buffer.Length);
        _a = 0;
        _b = 0;
        char c = await ReadNextChar();
        while(true) {
            while(c == ' ') {
                c = await ReadNextChar();
            }
            if(c == '\0') {
                Console.WriteLine("Connection closed");
                _conn.Close();
                return;
            }
            while(c != ' ') {
                if(c == '\0') {
                    Console.WriteLine("Connection closed prematurely");
                    _conn.Close();
                    return;
                }
                _a = _a * 10 + (byte)c - 48;
                c = await ReadNextChar();
            }
            while(c == ' ') {
                c = await ReadNextChar();
            }
            while(c != ' ') {
                if(c == '\0') {
                    await SendSum();
                    Console.WriteLine("Connection closed");
                    _conn.Close();
                    return;
                }
                _b = _b * 10 + (byte)c - 48;
                c = await ReadNextChar();
            }
            await SendSum();
            _a = 0;
            _b = 0;
        }
    }

    private async Task SendSum() {
        string s = string.Format("{0}", _a + _b);
        byte[] b = new byte[s.Length + 1];
        for(int i=0 ; i<s.Length ; ++i) {
            b[i] = (byte)s[i];
        }
        b[s.Length] = 10;
        await Send(_conn, b, 0, b.Length);
    }

    private static async Task MainLoop(Socket listeningSocket) {
        while(true) {
            Socket conn = await Accept(listeningSocket);
            Console.WriteLine("Connection opened");
            Session session = new Session(conn);
            Task dummy = session.Run();
        }
    }

    public static void Main(string[] args) {
        try {
            int port = Int32.Parse(args[0]);
            Console.WriteLine("Listening on port {0} ...", port);
            IPEndPoint listeningEndpoint = new IPEndPoint(IPAddress.Any, port);
            using(Socket listeningSocket = new Socket(AddressFamily.InterNetwork ,SocketType.Stream, ProtocolType.Unspecified)) {
                listeningSocket.Bind(listeningEndpoint);
                listeningSocket.Listen(10);
                Task dummy = MainLoop(listeningSocket);
                dummy.Wait();
            }
        } catch(Exception ex) {
            Console.WriteLine("Exception caught: {0}", ex);
        }
    }
    
    static Task<int> Receive(Socket conn, byte[] buf, int index, int count) {
        TaskCompletionSource<int> promise = new TaskCompletionSource<int>();
        conn.BeginReceive(buf, index, count, SocketFlags.None,
            (IAsyncResult ar)=> promise.SetResult(conn.EndReceive(ar)),
            null);
        return promise.Task;
    }

    static Task<int> Send(Socket conn, byte[] buf, int index, int count) {
        TaskCompletionSource<int> promise = new TaskCompletionSource<int>();
        conn.BeginSend(buf, index, count, SocketFlags.None,
            (IAsyncResult ar)=> promise.SetResult(conn.EndSend(ar)),
            null);
        return promise.Task;
    }

    static Task<Socket> Accept(Socket listeningSocket) {
        TaskCompletionSource<Socket> promise = new TaskCompletionSource<Socket>();
        listeningSocket.BeginAccept((IAsyncResult ar)=> promise.SetResult(listeningSocket.EndAccept(ar)), null);
        return promise.Task;
    }

    private Socket _conn;
    private byte[] _buffer;
    private int _pos;
    private int _size;
    private int _a, _b;
}
