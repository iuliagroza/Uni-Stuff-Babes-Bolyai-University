#!/bin/bash

# 3. Să se scrie un script bash care afișează primele 5 linii și ultimele 5 linii
# ale fișierelor de tip text dintr-un director dat ca argument în linia de comandă.
# Dacă un fișier are mai puțin de 10 linii, atunci va fi afişat în întregime.
# (comenzi: head, tail, find, file, wc)

# dacă nu există argumente în linia de comandă
if [ $# -eq 0 ]
then
    echo 'Numar insuficient de argumente.'
    echo 'Utilizare:' $0 'nume_director'                # afișez modul de utilizare
    exit 1                                              # termin execuția
fi

DIR=$1

for F in $(find $DIR -type f | sort)
do
    if file $F | grep -q 'ASCII text'                   # dacă fișierul e de tip text
    then
        echo -n "Fisier: "; echo $F | sed 's@.*/@@'     # extrag doar numele fișierului
        NL=$(cat $F | wc -l)                            # număr câte linii conține
        if [ $NL -lt 10 ]                               # dacă are mai puțin de 10 linii
        then
            cat -n $F                                   # îl afișez în întregime
        else
            echo "_____Head_____"
            head -n 5 $F                                # afișez primele 5 linii
            echo "_____Tail_____"
            tail -n 5 $F                                # afișez ultimele 5 linii
        fi
    fi
done

exit 0
