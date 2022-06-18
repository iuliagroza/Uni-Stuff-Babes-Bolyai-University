#!/bin/bash

# 1. Să se scrie un script bash care primeşte ca argument un număr natural N
# şi generează N fişiere de tip text, astfel:
# - numele fişierelor vor fi de forma: file_X.txt, unde X = {1, 2, ..., N}
# - fiecare fişier generat va conţine doar liniile de la X la X+5 ale fişierului /etc/passwd.

# dacă nu există argumente în linia de comandă
if [ $# -eq 0 ]
then
    echo 'Numar insuficient de argumente.'
    echo 'Utilizare:' $0 'numar_natural'    # afișez modul de utilizare
    exit 1                                  # termin execuția
fi

N=$1                                        # numărul natural N dat

# prima solutie
# -------------------------------------------------------------------------------------
for X in $(seq 1 $N)                                # pentru X de la 1..N
do
    touch "file_$X.txt"                             # creez fișierul
    sed -n ''$X',+5p' /etc/passwd >"file_$X.txt"    # scriu liniile de la X la X+5
done


# a doua solutie
# -------------------------------------------------------------------------------------
#X=1                                                # variabilă de ciclare
#while [ $X -le $N ]                                # cât timp X <= N
#do
#   touch "file_$X.txt"                             # creez fișierul
#   sed -n ''$X',+5p' /etc/passwd >"file_$X.txt"    # scriu liniile de la X la X+5
#   X=$[X+1]
#done

exit 0
