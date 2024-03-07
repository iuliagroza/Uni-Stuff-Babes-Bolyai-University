import socket
import random

def check_win(table):
    for i in range(3):
        if table[i] == table[i+3] == table[i+6]:
            if table[i] == 'X':
                message = "User won!"
                print(message)
                cs.send(message.encode("utf-8"))
                return True
            elif table[i] == "0":
                message = "Computer won!"
                print(message)
                cs.send(message.encode("utf-8"))
                return True
        if table[i] == table[i+1] == table[i+2]:
            if table[i] == 'X':
                message = "User won!"
                print(message)
                cs.send(message.encode("utf-8"))
                return True
            elif table[i] == "0":
                message = "Computer won!"
                print(message)
                cs.send(message.encode("utf-8"))
                return True

    if table[0] == table[4] == table[8]:
        if table[0] == 'X':
            message = "User won!"
            print(message)
            cs.send(message.encode("utf-8"))
            return True
        elif table[0] == "0":
            message = "Computer won!"
            print(message)
            cs.send(message.encode("utf-8"))
            return True

    if table[2] == table[4] == table[6]:
        if table[2] == 'X':
            message = "User won!"
            print(message)
            cs.send(message.encode("utf-8"))
            return True
        elif table[2] == "0":
            message = "Computer won!"
            print(message)
            cs.send(message.encode("utf-8"))
            return True
    return False

def check_tie(table):
    for i in range(9):
        if table[i] == '-':
            return False
    return True



s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(("172.25.12.101",6963))
s.listen(5)
cs,addr=s.accept()
b=cs.recv(10)
print(b)
done = False
table = "---------"
cs.send(table.encode("utf-8"))
while not done:
    b = cs.recv(100)
    table = b.decode("utf-8")
    print(table[:3])
    print(table[3:6])
    print(table[6:])

    if check_win(table):
        done = True

    if not check_tie(table):
        index = random.randint(0,8)
        while table[index] != '-':
            index = random.randint(0, 8)
        table=table[:index] + '0' + table[index+1:]
        cs.send(table.encode("utf-8"))

        if not done:
            if check_win(table):
                done = True
    else:
        done = True
        message = "It's a tie!"
        print(message)
        cs.send(message.encode("utf-8"))
cs.close()