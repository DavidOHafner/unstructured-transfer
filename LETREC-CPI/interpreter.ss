#!r7rs

;;; A continuation-passing interpreter for the LETREC language

;;; John David Stone
;;; Department of Computer Science
;;; Grinnell College

;;; Edited by Samantha Hafner

;;; This is an interpreter for the LETREC programming language
;;; using the continuation-passing style described in section 5.1
;;; of _Essentials of programming languages_, third edition
;;; (Cambridge, Massachusetts: The MIT Press, 2008; ISBN 978-0-262-06279-4),
;;; by Daniel P. Friedman and Mitchell Wand.
;;; The design and implementation extend,
;;; and are derived from, code published in that book.

;;; Extention to add lists as an expressed value are by
;;; Samantha Orion Hafner according to specifications by
;;; John David Stone. All code changes noted.

;;; created March 3, 2009
;;; last revised October 4, 2019

(define-library (LETREC-CPI interpreter)
  (export run)
  (import (scheme base)
          (utilities eopl)
          (LETREC syntax-trees)
          (LETREC parser)
          (LETREC expvals-and-environments)
          (LETREC-CPI continuations))
  (begin

    ;; run : String -> FinalAnswer

    (define run
      (lambda (source-text)
        (value-of-program (scan&parse source-text))))

    ;; value-of-program : Program -> FinalAnswer

    (define value-of-program
      (lambda (pgm)
        (cases program pgm
          (a-program (exp)
            (value-of/k exp (init-env) (end-cont))))))

    ;; value-of/k : Exp * Env * Cont -> FinalAnswer

    (define value-of/k
      (lambda (exp env cont)
        (cases expression exp
          (const-exp (datum) (apply-cont cont (num-val datum)))
          (var-exp (id) (apply-cont cont (apply-env env id)))
          (diff-exp (minuend subtrahend)
            (value-of/k minuend env (diff1-cont subtrahend env cont)))
          (zero?-exp (testee)
            (value-of/k testee env (zero1-cont cont)))
          (if-exp (condition consequent alternative)
            (value-of/k condition
                        env
                        (if-test-cont consequent alternative env cont)))
          (let-exp (bound-var bound-value body)
            (value-of/k bound-value env (let-exp-cont bound-var body env cont)))
          (proc-exp (parameter body)
            (apply-cont cont (proc-val (a-proc parameter body env))))
          (call-exp (operator operand)
            (value-of/k operator env (rator-cont operand env cont)))
          (letrec-exp (procedure-name parameter procedure-body letrec-body)
            (value-of/k letrec-body
                        (extend-env-rec procedure-name
                                        parameter
                                        procedure-body
                                        env)
                        cont))
          (emptylist-exp () (apply-cont cont (list-val '())));CHANGED to extend the continuation for
                                                            ;or immediatly evaluate list expressions
          (cons-exp (car-expression cdr-expression)
            (value-of/k car-expression env (cons1-cont cdr-expression env cont)))
          (null?-exp (testee)
            (value-of/k testee env (null?1-cont cont)))
          (car-exp (lst)
            (value-of/k lst env (car1-cont cont)))
          (cdr-exp (lst)
            (value-of/k lst env (cdr1-cont cont))))));end CHANGE

    ;; apply-procedure/k : Proc * ExpVal * Cont -> FinalAnswer

    (define apply-procedure/k
      (lambda (applicand argument cont)
        (cases proc applicand
          (a-proc (parameter body saved-env)
            (value-of/k body
                        (extend-env parameter argument saved-env)
                        cont)))))

    ;; The apply-cont procedure
    ;; receives a given expressed value
    ;; for which a given continuation is waiting,
    ;; and carries out the computation stored in the continuation
    ;; to obtain the final answer to a program.

    ;; apply-cont : Cont * ExpVal -> FinalAnswer

    (define apply-cont
      (lambda (cont val)
        (cases continuation cont
          (end-cont () (eopl:printf "End of computation.~%")
                       val)
          (diff1-cont (subtrahend env saved-cont)
            (value-of/k subtrahend env (diff2-cont val saved-cont)))
          (diff2-cont (minuend-value saved-cont)
            (apply-cont saved-cont (num-val (- (expval->num minuend-value)
                                               (expval->num val)))))
          (zero1-cont (saved-cont)
            (apply-cont saved-cont (bool-val (zero? (expval->num val)))))
          (if-test-cont (consequent alternative env saved-cont)
            (if (expval->bool val)
                (value-of/k consequent env saved-cont)
                (value-of/k alternative env saved-cont)))
          (let-exp-cont (bound-var body env saved-cont)
            (value-of/k body (extend-env bound-var val env) saved-cont))
          (rator-cont (operand env saved-cont)
            (value-of/k operand env (rand-cont val saved-cont)))
          (rand-cont (operator-value saved-cont)
            (apply-procedure/k (expval->proc operator-value)
                               val
                               saved-cont))
          (cons1-cont (cdr-expression env saved-cont);CHANGED to implement the execution of list
                                                     ;expression opperations from the continuation.
            (value-of/k cdr-expression env (cons2-cont val saved-cont)))
          (cons2-cont (car-value saved-cont)
            (apply-cont saved-cont (list-val (cons car-value
                                                   (expval->list val)))))
          (null?1-cont (saved-cont)
            (apply-cont saved-cont (bool-val (null? (expval->list val)))))
          (car1-cont (saved-cont)
            (if (null? (expval->list val))
              (report-empty-list-access-error 'car)
              (apply-cont saved-cont (car (expval->list val)))))
          (cdr1-cont (saved-cont)
            (if (null? (expval->list val))
              (report-empty-list-access-error 'cdr)
              (apply-cont saved-cont (list-val (cdr (expval->list val)))))))));end CHANGE
  
    (define report-empty-list-access-error
      (lambda (type)
        (eopl:error 'apply-cont
                    "~s was applied to an empty list."
                    type)))))


;;Tests
(import (scheme write))

;should be num-val 0
(display (run "0"))
(newline)
;should be num-val 0
(display (run "-(1, 0)"))
(newline)
;should be list '()
(display (run "emptylist"))
(newline)
;should be list (1)
(display (run "cons(1, emptylist)"))
(newline)
;should be list (1 2)
(display (run "cons(1, cons(2, emptylist))"))
(newline)
;should be 3
(display (run "
let l-123 = cons(1, cons(2, cons(3, emptylist))) in
 let l-lll = cons(l-123, cons(l-123, cons(l-123, emptylist))) in
  car(cdr(cdr(car(cdr(l-lll)))))
"))
(newline)
;should be 6
(display (run "
letrec sum(list) = if null?(list) then 0 else -((sum cdr(list)), -(0, car(list))) in
 (sum cons(1, cons(2, cons(3, emptylist))))
"))
(newline)
;should be 51
(display (run "
letrec sumif(list) = if null?(list) then 0 else if car(car(list)) then -((sumif cdr(list)), -(0, car(cdr(car(list))))) else (sumif cdr(list)) in
 let make = proc (test) proc (val) cons(test, cons(val, emptylist)) in
  let true = zero?(0) in let false = zero?(1) in
  (sumif cons(((make true) 3), cons(((make false) 13), cons(((make true) 31), cons(((make true) 17), cons(((make false) 71), emptylist))))))
"))
(newline)

;Error tests
;(run "cons(1, 1)") ;expval->list should fail
;(run "null?(1)") ;expval->list should fail
;(run "car(zero?(1))") ;expval->list should fail
;(run "car(emptylist)") ;should specify car to empty list error
;(run "cdr(emptylist)") ;should specify cdr to empty list error


;;; As mentioned above,
;;; the procedure definitions are derived from
;;; the work of Friedman and Wand,
;;; who published them on Mitchell Wand's Github site,
;;; as part of the repository https://github.com/mwand/eopl3,
;;; under the Creative Commons Attribution-Noncommercial 3.0 Unported License.

;;; The port to R7RS Scheme is copyright (C) 2009, 2015, 2019 by John David Stone
;;; and is likewise released
;;; under the Creative Commons Attribution-Noncommercial 3.0 Unported License.

;;; The extention to add lists as an expressed value and coresponding tests, if any,
;;; are copytight (C) 2019 by Samantha Orion Hafner and are likewise released
;;; under the Creative Commons Attribution-Noncommercial 3.0 Unported License.