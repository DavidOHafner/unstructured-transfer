#!r7rs

;;; A continuation-passing interpreter for the LETREC language, in imperative style

;;; John David Stone
;;; Department of Computer Science
;;; Grinnell College

;;; This is an interpreter for the LETREC programming language
;;; using continuation passing through registers,
;;; as described in section 5.3
;;; of _Essentials of programming languages_, third edition
;;; (Cambridge, Massachusetts: The MIT Press, 2008; ISBN 978-0-262-06279-4),
;;; by Daniel P. Friedman and Mitchell Wand.
;;; The design and implementation extend,
;;; and are derived from, code published in that book.

;;; created March 8, 2009
;;; last revised July 22, 2019

(define-library (LETREC-IMP interpreter)
  (export run)
  (import (scheme base)
          (utilities eopl)
          (LETREC syntax-trees)
          (LETREC parser)
          (LETREC expvals-and-environments)
          (LETREC-CPI continuations))
  (begin

    ;; The following global variables are used as registers
    ;; by the procedures that make up the interpreter.

    (define exp-reg 'uninitialized)
    (define env-reg 'uninitialized)
    (define cont-reg 'uninitialized)
    (define val-reg 'uninitialized)
    (define proc-reg 'uninitialized)

    ;; run : String -> FinalAnswer

    (define run
      (lambda (source-text)
        (value-of-program (scan&parse source-text))))

    ;; value-of-program : Program -> FinalAnswer

    (define value-of-program
      (lambda (pgm)
        (cases program pgm
          (a-program (exp)
            (set! cont-reg (end-cont))
            (set! exp-reg exp)
            (set! env-reg (init-env))
            (value-of/k)))))

    ;; value-of/k : () -> FinalAnswer

    (define value-of/k
      (lambda ()
        (cases expression exp-reg
          (const-exp (datum)
            (set! val-reg (num-val datum))
            (apply-cont))
          (var-exp (id)
            (set! val-reg (apply-env env-reg id))
            (apply-cont))
          (diff-exp (minuend subtrahend)
            (set! cont-reg (diff1-cont subtrahend env-reg cont-reg))
            (set! exp-reg minuend)
            (value-of/k))
          (zero?-exp (testee)
            (set! cont-reg (zero1-cont cont-reg))
            (set! exp-reg testee)
            (value-of/k))
          (if-exp (condition consequent alternative)
            (set! cont-reg (if-test-cont consequent alternative env-reg cont-reg))
            (set! exp-reg condition)
            (value-of/k))
          (let-exp (bound-var bound-value body)
            (set! cont-reg (let-exp-cont bound-var body env-reg cont-reg))
            (set! exp-reg bound-value)
            (value-of/k))
          (proc-exp (parameter body)
            (set! val-reg (proc-val (a-proc parameter body env-reg)))
            (apply-cont))
          (call-exp (operator operand)
            (set! cont-reg (rator-cont operand env-reg cont-reg))
            (set! exp-reg operator)
            (value-of/k))
          (letrec-exp (procedure-name parameter procedure-body letrec-body)
            (set! env-reg (extend-env-rec procedure-name
                                          parameter
                                          procedure-body
                                          env-reg))
            (set! exp-reg letrec-body)
            (value-of/k)))))

    ;; apply-procedure/k : () -> FinalAnswer

    (define apply-procedure/k
      (lambda ()
        (cases proc proc-reg
          (a-proc (parameter body saved-env)
            (set! exp-reg body)
            (set! env-reg (extend-env parameter val-reg saved-env))
            (value-of/k)))))

    ;; The apply-cont procedure
    ;; recovers an expressed value from the val register
    ;; and a continuation that is awaiting that value
    ;; from the cont register,
    ;; and carries out the computation stored in the continuation
    ;; to obtain the final answer to a program.

    ;; apply-cont : () -> FinalAnswer

    (define apply-cont
      (lambda ()
        (cases continuation cont-reg
          (end-cont ()
            (eopl:printf "End of computation.~%")
            val-reg)
          (diff1-cont (subtrahend env saved-cont)
            (set! cont-reg (diff2-cont val-reg saved-cont))
            (set! exp-reg subtrahend)
            (set! env-reg env)
            (value-of/k))
          (diff2-cont (minuend-value saved-cont)
            (set! cont-reg saved-cont)
            (set! val-reg (num-val (- (expval->num minuend-value)
                                      (expval->num val-reg))))
            (apply-cont))
          (zero1-cont (saved-cont)
            (set! cont-reg saved-cont)
            (set! val-reg (bool-val (zero? (expval->num val-reg))))
            (apply-cont))
          (if-test-cont (consequent alternative env saved-cont)
            (set! cont-reg saved-cont)
            (if (expval->bool val-reg)
                (set! exp-reg consequent)
                (set! exp-reg alternative))
            (set! env-reg env)
            (value-of/k))
          (let-exp-cont (bound-var body env saved-cont)
            (set! cont-reg saved-cont)
            (set! exp-reg body)
            (set! env-reg (extend-env bound-var val-reg env))
            (value-of/k))
          (rator-cont (operand env saved-cont)
            (set! cont-reg (rand-cont val-reg saved-cont))
            (set! exp-reg operand)
            (set! env-reg env)
            (value-of/k))
          (rand-cont (operator-value saved-cont)
            (set! cont-reg saved-cont)
            (set! proc-reg (expval->proc operator-value))
            (apply-procedure/k)))))))

;;; As mentioned above,
;;; the procedure definitions are derived from
;;; the work of Friedman and Wand,
;;; who published them on Mitchell Wand's Github site,
;;; as part of the repository https://github.com/mwand/eopl3,
;;; under the Creative Commons Attribution-Noncommercial 3.0 Unported License.

;;; The port to R7RS Scheme is copyright (C) 2009, 2015, 2019 by John David Stone
;;; and is likewise released
;;; under the Creative Commons Attribution-Noncommercial 3.0 Unported License.
