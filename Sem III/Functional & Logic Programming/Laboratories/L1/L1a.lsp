; a) Write a function that merges two sorted linear lists and keeps double values.

; Mathematical model:
; merge(l1l2...ln, k1k2...km) = {
;                                     k1k2...km, if n = 0
;                                     l1l2...ln, if m = 0
;                                     {l1} U merge(l2...ln, k1k2...km), if l1 <= k1
;                                     {k1} U merge(l1l2...ln, k2k3...km), otherwise
;                               }

(defun merges (a b)
    (cond
        ((null a) b)
        ((null b) a)
        ((> (car a) (car b)) (cons (car b) (merges a (cdr b))))
        (T (cons (car a) (merges (cdr a) b)))
    )
)

; Testing examples:
; 1. (merges '(1 2 3 4 5) '(0 2 4 4 9 10)) => (0 1 2 2 3 4 4 4 5 9 10)
; 2. (merges '() '(0 2 4 4 9 10)) => (0 2 4 4 9 10)
; 3. (merges '(1 2 3 4 5) '()) => (1 2 3 4 5)
; 4. (merges '() '()) => NIL
; 5. (merges '(1) '(-23 45 67)) => (-23 1 45 67)


; b) Write a function to replace an element E by all elements of a list L1 at all levels of a given list L.

; Mathematical model:
; my_replace(l1l2...ln, k1k2...kn, e) = {    
;                                             0, if n = 0
;                                             k1k2...kn U my_replace(l2l3...ln), if l1 = e
;                                             {l1} U my_replace(l2l3...ln), otherwise
;                                       }


(defun my_append (l1 l2)
    (COND 
        ((null l1) l2)
        ((null l2) l1)
        (T (cons (car l1) (my_append (cdr l1) l2)) 
        )
    )
)

(defun my_replace (l1 l2 e r)
    (cond 
        ((null l1) r)
        (
            (equal (car l1) e)
            (my_replace (cdr l1) l2 e (my_append r l2))
        )
        (
            T 
            (my_replace (cdr l1) l2 e (my_append r (list (car l1))))
        )
    )
)

; Testing examples:
; 1. (my_replace '(1 2 3 4 5) '(0 2 4 4 9 10) 4 '()) => (1 2 3 0 2 4 4 9 10 5)
; 2. (my_replace '(1 2 3 4 5) '(-1) 1 '()) => (-1 2 3 4 5)
; 3. (my_replace '(1 2 3 4 5) '() 5 '()) => (1 2 3 4)
; 4. (my_replace '(1 2 3 4 5) '(0 2 4 4 9 10) 6 '()) => (1 2 3 4 5)
; 5. (my_replace '(1 2 3 4 5) '(0 2 4 4 9 10) 0 '()) => (1 2 3 4 5)

; c) Write  a  function  which  determines  the  sum  of  two  numbers  in  list  representation,  and  returns  
; corresponding  decimal  number, without  transforming  the  representation  of  the  number  from  list  to number.

; Mathematical model:
; cat(l1l2...ln, k1k2...km) = {
;                                 k1k2...km, if n = 0
;                                 {l1} U k1k2...km, if l2l3...ln atom
;                                 {l1} U cat(l2...ln, k1k2...km), otherwise

(defun cat (l1 l2) 
    (cond
        ((null l1) l2)
        ((atom (cdr l1)) (cons (car l1) l2)) 
        (T (cons (car l1) (cat (cdr l1) l2)))
    ) 
)

; Mathematical model:
; rev(l1l2...ln) = {
;                     0, if n = 0
;                     cat(rev(l2...ln), {l1}), otherwise
;                  }

(defun rev (l)
    (cond
        ((null l) ())
        (T (cat (rev (cdr l)) (list (car l))))
    )
)

; Mathematical model:  
; sumL(l1l2...ln, k1k2...km) = {
;                                 0, if n = 0 and m = 0
;                                 l1l2...ln, if m = 0
;                                 k1k2...km, if n = 0
;                                 {l1 + k1} U sumL(l2...ln, k2...km), if l1 + k1 < 10
;                                 {l1 + k1 - 10} U sumL({l2+1}Ul3l4...ln, k2...km), otherwise
;                             }

(defun sum_l (l1 l2)
    (cond 
        ((and (null l1) (null l2)) ())
        ((null l1) l2)
        ((null l2) l1)
        (
            (< (+ (car l1) (car l2)) 10)
            (cons (+ (car l1) (car l2)) (sum_l (cdr l1) (cdr l2)))
        )
        (
            T
            (if (atom (cdr l1)) 
                (setq l1 (cat l1 (list 0)))
            )
            (if (atom (cdr l2)) 
                (setq l2 (cat l2 (list 0)))
            )
            (cons (- (+ (car l1) (car l2)) 10) (sum_l (cons (+ (car (cdr l1)) 1) (cdr(cdr l1))) (cdr l2)))
        )
    )
)

(defun sum_wrapper (l1 l2)
    (rev (sum_l (rev l1) (rev l2)))
)

; Testing examples:
; 1. (sum_wrapper '(1 2 3 4 5) '(2 5 9 9 8)) => (3 8 3 4 3)
; 2. (sum_wrapper '() '(2 4 4 9 5)) => (2 4 4 9 5)
; 3. (sum_wrapper '(1 2 3 4 5) '(9 9 9 9 9 9)) => (1 0 1 2 3 4 4)
; 4. (sum_wrapper '() '()) => NIL
; 5. (sum_wrapper '(1) '(9 9 9)) => (1 0 0 0)

; d) Write a function to return the greatest common divisor of all numbers in a linear list.

; Mathematical model:
; gcd(a, b) = {
;                     gcd(b, a%b), if b != 0
;                     a, otherwise
;             }


(defun gcd_ (a b)
    (cond 
        ((and (not (numberp a)) (not (numberp b))) nil)
        ((not (numberp a)) b)
        ((not (numberp b)) a)
        ((< a b) (gcd_ b a))
        ((equal b 0) a)
        (T (gcd_ b (mod a b)))
    )
)

; Mathematical model:
; gcd_list(l1l2...ln) = {
;                             l1, if n = 1
;                             gcd(l1, l2), if n = 2
;                             gcd(l1, gcd_list(l2l3...ln)), otherwise
;                       }

(defun gcd_list(a aux)
    (cond 
        ((null a) aux)
        (
            (listp (car a))
            (gcd_list (car a) aux)
        )
        (
            T 
            (atom a) 
            (gcd_list (cdr a) (gcd_ (car a) aux))
        )
    )

)

; Testing examples:
; 1. (gcd_list '(1 2 3 4 5) 0) => 1
; 2. (gcd_list '(10 255 30 45 5) 0) => 5
; 3. (gcd_list '() 0) => 0
; 4. (gcd_list '(10 20 2) 0) => 2
; 5. (gcd_list '(15 5 10 5) 0) => 5