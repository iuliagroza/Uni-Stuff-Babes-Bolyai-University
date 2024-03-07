; 8. Write a function to determine the number of nodes on the level k from a n-tree represented as follows:
;    (root list_nodes_subtree1 ... list_nodes_subtreen)
;     Eg: tree is (a (b (c)) (d) (e (f))) and k=1 => 3 nodes

; Mathematical model:
; no_of_nodes(l1l2...ln, k, c) = {
;                                   1, if k = c and l1l2...ln = atom
;                                   0, if k != c and l1l2...ln = atom
;                                   no_of_nodes(l1, k, c) + no_of_nodes(l2, k, c) + ... + no_of_nodes(ln, k, c), otherwise
;                              }

(defun no_of_nodes(l k c)
  (cond
    ((and (atom l) (equal c k)) 1)
    ((atom l) 0)
    (t (apply '+ (mapcar #' (lambda (a) (no_of_nodes a k (+ c 1))) l)))
  )
)


(defun main(l k)
  (no_of_nodes l k -1)
)

; Testing examples:
; 1. (main '(1 (2 (3)) (4) (5 (6))) 1) => 3
; 2. (main '(1) 1) => 0
; 3. (main '(1) 0) => 1
; 4. (main '(1 (2 (3)) (4) (5 (6))) 2) => 2
; 5. (main '(5 () (1 (3) (4 (2) (7 (8) (9))))) 2) => 2