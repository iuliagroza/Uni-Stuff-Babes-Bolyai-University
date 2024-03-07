; Mathematical model:
; mountain(l1l2...ln, f) = {
;                               true, if n <= 1 and f = 1
;                               false, if n <= 1 and f = 0
;                               mountain(l2...ln, 0), if l1 < l2 and f = 0
;                               mountain(l2...ln, 1), if l1 > l2 and f = 0
;                               mountain(l2...ln, 1), if l1 > l2 and f = 1
;                               false, otherwise
;                          }

(defun mountain(l f)
  (cond
    ((and (null (cdr l)) (= f 1)) t)
    ((and (null (cdr l)) (= f 0)) nil)
    ((and (< (car l) (cadr l)) (= f 0)) (mountain (cdr l) 0))
    ((and (> (car l) (cadr l)) (= f 0)) (mountain (cdr l) 1))
    ((and (> (car l) (cadr l)) (= f 1)) (mountain (cdr l) 1))
    (t nil)
  )
)

; Mathematical model:
; main(l1l2...ln) = {
;                       false, if n < 3
;                       false, if l1 > l2
;                       mountain(l1l2...ln, 0) , otherwise
;                    }
;
; main(l1l2...ln) = {
;                       nil, if l1 is null
;                       nil, if l2 is null
;                       nil, if l3 is null
;                       nil, if (car l) > (cadr l)
;                       mountain(l1l2...ln, 0) , otherwise
;                   }

(defun main(l)
  (cond
    ((null l) nil)
    ((null (cadr l)) nil)
    ((null (caddr l)) nil)
    ((> (car l) (cadr l)) nil)
    (t (mountain l 0))
  )
)
