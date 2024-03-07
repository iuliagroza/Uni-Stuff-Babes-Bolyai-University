import socket

IP = "0.0.0.0"
PORT = 5555

MSG = "hello from server"
BYTES = 256


def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind((IP, PORT))

    buff, addr = s.recvfrom(BYTES)
    print(buff.decode())

    s.sendto(str.encode(MSG), addr)


if __name__ == "__main__":
    main()
