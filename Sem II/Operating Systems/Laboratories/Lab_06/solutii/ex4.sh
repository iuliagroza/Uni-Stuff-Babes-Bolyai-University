#!/bin/bash

# 4. Să se scrie un script bash care afișează numele fișierelor dintr-un
# director dat ca parametru care conțin numere cu peste 5 cifre.

# dacă nu există argumente în linia de comandă
if [ $# -eq 0 ]
then
    echo 'Numar insuficient de argumente.'
    echo 'Utilizare:' $0 'nume_director'                # afișez modul de utilizare
    exit 1                                              # termin execuția
fi

DIR=$1

for F in $(find $DIR -type f)                           # pentru fiecare fișier F din directorul DIR
do
    if cat $F | grep -Eq '[0-9]{5,}'                    # dacă conține numere cu peste 5 cifre
    then
        NF=$(echo $F | sed 's@.*/@@')                   # extrag doar numele fișierului
        echo 'Fisier:' $NF                              # afișez numele fișierului
    fi
done

exit 0
