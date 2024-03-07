import socket

IP = "172.30.113.29"
PORT = 5555

MSG = "hello from client"
BYTES = 256


def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.sendto(str.encode(MSG), (IP, PORT))

    result, _ = s.recvfrom(BYTES)
    print(result.decode())


if __name__ == "__main__":
    main()
