// A server that accepts pairs of numbers, transmitted as text and separated by whitespace, and sends back their sums

using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;

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
        _conn.BeginReceive(_buffer, 0, _buffer.Length, SocketFlags.None, (IAsyncResult ar)=> this.OnBytesReceived(ar), null);
    }

    private void OnBytesReceived(IAsyncResult ar) {
        _size = _conn.EndReceive(ar);
        _pos = 0;
        ProcessBuffer();
    }

    private void SendSum(bool isLast) {
        string s = string.Format("{0}\n", _a + _b);
        byte[] b = new byte[s.Length + 1];
        for(int i=0 ; i<s.Length ; ++i) {
            b[i] = (byte)s[i];
        }
        b[s.Length] = 10;
        if(isLast) {
            _conn.BeginSend(b, 0, b.Length, SocketFlags.None, OnLastSendDone, null);
        } else {
            _conn.BeginSend(b, 0, b.Length, SocketFlags.None, OnSendDone, null);
        }
    }

    private void OnSendDone(IAsyncResult ar) {
        _conn.EndSend(ar);
        ProcessBuffer();
    }

    private void OnLastSendDone(IAsyncResult ar) {
        _conn.EndSend(ar);
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

        _conn.BeginReceive(_buffer, 0, _buffer.Length, SocketFlags.None, OnBytesReceived, null);
    }

    private static void OnNewConnection(Socket listeningSocket, IAsyncResult ar) {
        Socket conn = listeningSocket.EndAccept(ar);
        Console.WriteLine("Connection opened");
        Session newSession = new Session(conn);
        newSession.Start();
        listeningSocket.BeginAccept((IAsyncResult ar1) => OnNewConnection(listeningSocket, ar1), null);
    }

    public static void Main(string[] args) {
        try {
            int port = Int32.Parse(args[0]);
            Console.WriteLine("Listening on port {0} ...", port);
            IPEndPoint listeningEndpoint = new IPEndPoint(IPAddress.Any, port);
            using(Socket listeningSocket = new Socket(AddressFamily.InterNetwork ,SocketType.Stream, ProtocolType.Unspecified)) {
                listeningSocket.Bind(listeningEndpoint);
                listeningSocket.Listen(10);
                listeningSocket.BeginAccept((IAsyncResult ar) => OnNewConnection(listeningSocket, ar), null);
                while(true) {
                    Thread.Sleep(10000);
                }
            }
        } catch(Exception ex) {
            Console.WriteLine("Exception caught: {0}", ex);
        }
    }

    private Socket _conn;
    private byte[] _buffer;
    private int _pos;
    private int _size;
    private State _state;
    private int _a, _b;
}
