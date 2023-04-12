;###################################################################
;# David Huson                                                     #
;# Programming Languages - COP 4020                                #
;# Project 4                                                       #
;# part2.lisp                                                      #
;# the python-generated lisp program to test strings with an fsa   #
;###################################################################
(setq fsa '((0 0 x) (0 1 y) (1 2 x) (2 2 x) (2 3 y) (3 3 x) (3 4 z) (4 4 x) (4 2 y) (4 1 a)))
(setq initialState '(0))
(setq acceptStates '(1 3))
(setq alphabet '(x y z a))

(defun testFSA(inputStringAsList state)
  (cond 
    ((null inputStringAsList) 
      (if (member state acceptStates)
        (format nil "Accepted!")
      ;else
      (format nil "Not Accepted!"))
    )
    (t 
      (dolist (transition fsa)
        (setq c (car inputStringAsList))
        (setq tState (car transition))
        (setq token (caddr transition))
        (setq nState (cadr transition))
        (unless ;; if c is not in the alphabet, print "Not Accepted" and exit exicution
          (member c alphabet)
          (setq state -1) (return NIL) 
        )
        (if (eq T (applyTransition state))
            (setq state nState)
            ; else
            (format nil "Not Accepted!")
        )
      ) 
      (testFSA (cdr inputStringAsList) state)
    )
  )
)

(defun applyTransition (state)
  (if (and (eq state tState) (eq c token))
      ;; (setq state nState)
      (return-from applyTransition T)
      ; else
      (return-from applyTransition nil)
  )
)
(defun demo()
  (setq fp (open "theString.txt" :direction :input))
  (setq input (read fp nil))
  (princ "processing ")
  (princ input)
  (testFSA input (car initialState))
)