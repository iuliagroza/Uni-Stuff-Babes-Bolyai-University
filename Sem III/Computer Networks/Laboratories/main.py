import time
import socket
import random
from threading import Thread

words = ["serendipity", "exhausted", "owl", "hangman", "computer", "networks", "test", "lab"]

def return_index(letter, word, guessed_word):
    index = 1
    for let in word:
        if letter == let and guessed_word[index-1]=='-':
            return index
        index+=1
    return -1


def f(cs,i):
 print ("Procesez client "+str(i))

 index = random.randint(0, len(words)-1)
 guess_word = words[index]
 guessed_word = ""
 trials = len(guess_word) + 3
 for letter in guess_word:
     guessed_word += "-"
 print(guess_word)

 done = False
 while not done:
     letter = cs.recv(10).decode("utf-8")
     trials -= 1

     print(letter)
     index_letter = return_index(letter, guess_word, guessed_word)
     if index_letter == -1:
         message = "Letter not in the word!\n"
         cs.send(message.encode("utf-8"))
         status = cs.recv(10).decode("utf-8")
         print(guessed_word)
         cs.send(guessed_word.encode("utf-8"))
         status = cs.recv(10).decode("utf-8")
         if guess_word == guessed_word:
             message = "User won.\n"
             print(message)
             cs.send(message.encode("utf-8"))
             status = cs.recv(10).decode("utf-8")
             done = True
         else:
             if trials == 0:
                 message = "User lost.\n"
                 print(message)
                 cs.send(message.encode("utf-8"))
                 status = cs.recv(10).decode("utf-8")
                 done = True
             else:
                 message = "Trials: " + str(trials) + "\n"
                 print(message)
                 cs.send(message.encode("utf-8"))
                 status = cs.recv(10).decode("utf-8")
                 done = False
     else:
         cs.send(str(index_letter).encode("utf-8"))
         status = cs.recv(10).decode("utf-8")
         guessed_word = guessed_word[:index_letter-1] + letter + guessed_word[index_letter:]
         print(guessed_word)
         cs.send(guessed_word.encode("utf-8"))
         status = cs.recv(10).decode("utf-8")
         if guess_word == guessed_word:
             message = "User won.\n"
             print(message)
             cs.send(message.encode("utf-8"))
             status = cs.recv(10).decode("utf-8")
             done = True
         else:
             if trials == 0:
                 message = "User lost.\n"
                 print(message)
                 cs.send(message.encode("utf-8"))
                 status = cs.recv(10).decode("utf-8")
                 done = True
             else:
                 message = "Trials: " + str(trials) + "\n"
                 print(message)
                 cs.send(message.encode("utf-8"))
                 status = cs.recv(10).decode("utf-8")
                 done = False

 #cs.send(str(i).encode("utf-8"))
 #cs.send(guess_word.encode("utf-8"))
 cs.close()
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(("172.30.113.134",7764))
s.listen(5)
i=0
while (1==1):
 i=i+1
 cs,addr=s.accept()
 t=Thread(target=f,args=(cs,i,))
 t.start()
