; 13. For a given tree of type (2) return the path from the root node to a certain given node X.

; Mathematical model:
; my_append(l1l2...ln, p1p2...pm) = {
;                                       p1p2...pm, if n = 0
;                                       {l1} U my_append(l2...ln, p1p2...pm), otherwise
;                                  }

(defun my_append (l p)
  (cond
    ((null l) p)
    (t (cons (car l) (my_append (cdr l) p)))
  )
)

; Mathematical model:
; check_existence(l1l2...ln, elem) = { 
;                                       false, if n = 0
;                                       true, if l1 = elem
;                                       check_existence(l1, elem) or check_existence(l2...ln, elem), if l1 is a list
;                                       check_existence(l2...ln, elem), otherwise
;                                   }

(defun check_existence(l elem)
  (cond
    ((null l) nil)
    ((equal (car l) elem) t)
    ((listp (car l)) (or (check_existence (car l) elem) (check_existence (cdr l) elem)))
    (t (check_existence (cdr l) elem))
  )
)

; Mathematical model:
; path(l1l2l3, elem) = {
;                           0, if l1l2l3 = 0
;                           l1, if elem = l1
;                           path(l2), if check_existence(l2) = true
;                           path(l3), if check_existence(l3) = true
;                      }

(defun path(l elem)
  (cond 
    ((null l) nil)
    ((equal (car l) elem) (list (car l)))
    ((check_existence (cadr l) elem) (cons (car l) (path (cadr l) elem)))
    ((check_existence (caddr l) elem) (cons (car l) (path (caddr l) elem)))
  )
)

; Testing examples:
; 1. (path '(1 (2) (3 (4) (5))) 5) => (1 3 5)
; 2. (path '(1) 1) => (1)
; 3. (path '(1 (2) (3 (4) (5))) 6) => NIL
; 4. (path '(1 (2 (3 (4 (5 (6)))))) 4) => (1 2 3 4)
; 5. (path '(5 () (1 (3) (4 (2) (7 (8) (9))))) 9) => (5 1 4 7 9)