// A server that accepts pairs of numbers, transmitted as text and separated by whitespace, and sends back their sums

using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;

class Session {
    enum State {BeforeFirst, ReadingFirst, BeforeSecond, ReadingSecond}

    private Session(Socket conn) {
        _conn = conn;
        _buffer = new byte[10];
    }

    private void Start() {
        _pos = 0;
        _state = State.BeforeFirst;
        _a = 0;
        _b = 0;
        Task<int> future = Receive(_conn, _buffer, 0, _buffer.Length);
        future.ContinueWith(OnBytesReceived);
    }

    private void OnBytesReceived(Task<int> future) {
        _size = future.Result;
        _pos = 0;
        ProcessBuffer();
    }

    private void SendSum(bool isLast) {
        string s = string.Format("{0}", _a + _b);
        byte[] b = new byte[s.Length + 1];
        for(int i=0 ; i<s.Length ; ++i) {
            b[i] = (byte)s[i];
        }
        b[s.Length] = 10;
        Task<int> future = Send(_conn, b, 0, b.Length);
        if(isLast) {
            future.ContinueWith(OnLastSendDone);
        } else {
            future.ContinueWith(OnSendDone);
        }
    }

    private void OnSendDone(Task<int> future) {
        ProcessBuffer();
    }

    private void OnLastSendDone(Task<int> future) {
        _conn.Close();
    }

    private void ProcessBuffer() {
        if(_size == 0) {
            switch(_state) {
            case State.BeforeFirst:
                Console.WriteLine("Connection closed");
                _conn.Close();
                return;
            case State.ReadingSecond:
                SendSum(true);
                return;
            default:
                Console.WriteLine("Connection closed prematurely");
                _conn.Close();
                return;
            }
        }

        while(_pos < _size) {
            byte b = _buffer[_pos];
            char c = (char)b;
            ++_pos;
            if(c == '\n' || c == '\r' || c == '\t') {
                c = ' ';
            } else if(c != ' ' && (c<'0' || c>'9')) {
                Console.WriteLine("Unexpected caracter: {0}", c);
                c = ' ';
            }
            switch(_state) {
            case State.BeforeFirst:
                if(c >= '0' && c <= '9') {
                    _state = State.ReadingFirst;
                    _a = b-48;
                }
                break;
            case State.ReadingFirst:
                if(c >= '0' && c <= '9') {
                    _a = _a*10+b-48;
                } else {
                    _state = State.BeforeSecond;
                }
                break;
            case State.BeforeSecond:
                if(c >= '0' && c <= '9') {
                    _state = State.ReadingSecond;
                    _b = b-48;
                }
                break;
            case State.ReadingSecond:
                if(c >= '0' && c <= '9') {
                    _b = _b*10+b-48;
                } else {
                    _state = State.BeforeFirst;
                    SendSum(false);
                    return;
                }
                break;
            }
        }

        Task<int> future = Receive(_conn, _buffer, 0, _buffer.Length);
        future.ContinueWith(OnBytesReceived);
    }

    private static void OnNewConnection(Socket listeningSocket, Task<Socket> f) {
        Socket conn = f.Result;
        Console.WriteLine("Connection opened");
        Session newSession = new Session(conn);
        newSession.Start();
        Task<Socket> future = Accept(listeningSocket);
        future.ContinueWith((Task<Socket> f2) => OnNewConnection(listeningSocket, f2));
    }

    public static void Main(string[] args) {
        try {
            int port = Int32.Parse(args[0]);
            Console.WriteLine("Listening on port {0} ...", port);
            IPEndPoint listeningEndpoint = new IPEndPoint(IPAddress.Any, port);
            using(Socket listeningSocket = new Socket(AddressFamily.InterNetwork ,SocketType.Stream, ProtocolType.Unspecified)) {
                listeningSocket.Bind(listeningEndpoint);
                listeningSocket.Listen(10);
                Task<Socket> future = Accept(listeningSocket);
                future.ContinueWith((Task<Socket> f) => OnNewConnection(listeningSocket, f));
                while(true) {
                    Thread.Sleep(1000000);
                }
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
    private State _state;
    private int _a, _b;
}
