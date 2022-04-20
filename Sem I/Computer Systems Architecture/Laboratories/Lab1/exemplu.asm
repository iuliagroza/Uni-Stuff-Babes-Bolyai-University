bits 32 ;asamblare și compilare pentru arhitectura de 32 biți
; definim punctul de intrare in programul principal
global start

; declaram functiile externe necesare programului nostru 
extern exit ; indicam asamblorului ca exit exista, chiar daca noi nu o vom defini
import exit msvcrt.dll  ; exit este o functie care incheie procesul, este definita in msvcrt.dll
        ; msvcrt.dll contine exit, printf si toate celelalte functii C-runtime importante

; segmentul de date in care se vor defini variabilele 
segment data use32 class=data
; A DB 0A2h ;se declara variabila a de tip BYTE si se initializeaza cu valoarea 0A2h
; B DW 'ab' ;se declara variabila a de tip WORD si se initializeaza cu valoarea 'ab'
; C DD 12345678h ;se declara variabila a de tip DOUBLE WORD si se initializeaza cu valoarea 12345678h
; D DQ 1122334455667788h ;se declara variabila a de tip QUAD WORD si se initializeaza cu valoarea 1122334455667788h
; a DB 02
; b DB 02h
; c DB 102
a DW  123423
b DW 12375h
c DW 'aaaaaaaaaaazzzzzz'
d DW 1020

; segmentul de cod
segment code use32 class=code
start:
; ... 

    ; exit(0)
    push dword 0 ; se pune pe stiva parametrul functiei exit
    call [exit] ; apelul functiei exit pentru terminarea executiei programului