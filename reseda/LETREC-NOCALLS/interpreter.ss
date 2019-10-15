#!r7rs

;;; A continuation-passing interpreter for the LETREC language, in imperative style

;;; John David Stone
;;; Department of Computer Science
;;; Grinnell College

;;; This is an interpreter for the LETREC programming language
;;; using continuation passing through shared variables,
;;; as described in section 5.3
;;; of _Essentials of programming languages_, third edition
;;; (Cambridge, Massachusetts: The MIT Press, 2008; ISBN 978-0-262-06279-4),
;;; by Daniel P. Friedman and Mitchell Wand.
;;; The design and implementation extend,
;;; and are derived from, code published in that book.

;;; created March 8, 2009
;;; last revised October 4, 2019

(define-library (LETREC-NOCALLS interpreter)
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
        (cases program (scan&parse source-text)
          (a-program (exp)
            (let ((cont-reg (end-cont))
                  (exp-or-proc-reg exp)
                  (val-or-env-reg (init-env))
                  (selector 'value-of/k))
              (do ()
                  ((eq? selector 'done) val-or-env-reg)
                (case selector
                  ((value-of/k)
                   (cases expression exp-or-proc-reg
                     (const-exp (datum)
                       (set! val-or-env-reg (num-val datum))
                       (set! selector 'apply-cont))
                     (var-exp (id)
                       (set! val-or-env-reg (apply-env val-or-env-reg id))
                       (set! selector 'apply-cont))
                     (diff-exp (minuend subtrahend)
                       (set! cont-reg
                             (diff1-cont subtrahend val-or-env-reg cont-reg))
                       (set! exp-or-proc-reg minuend))
                     (zero?-exp (testee)
                       (set! cont-reg (zero1-cont cont-reg))
                       (set! exp-or-proc-reg testee))
                     (if-exp (condition consequent alternative)
                       (set! cont-reg (if-test-cont consequent alternative
                                                    val-or-env-reg cont-reg))
                       (set! exp-or-proc-reg condition))
                     (let-exp (bound-var bound-value body)
                       (set! cont-reg (let-exp-cont bound-var body
                                                    val-or-env-reg cont-reg))
                       (set! exp-or-proc-reg bound-value))
                     (proc-exp (parameter body)
                       (set! val-or-env-reg 
                             (proc-val (a-proc parameter body val-or-env-reg)))
                       (set! selector 'apply-cont))
                     (call-exp (operator operand)
                       (set! cont-reg (rator-cont operand val-or-env-reg cont-reg))
                       (set! exp-or-proc-reg operator))
                     (letrec-exp (procedure-name parameter procedure-body letrec-body)
                       (set! val-or-env-reg (extend-env-rec procedure-name
                                                            parameter
                                                            procedure-body
                                                            val-or-env-reg))
                       (set! exp-or-proc-reg letrec-body))))
                  ((apply-procedure/k)
                   (cases proc exp-or-proc-reg
                     (a-proc (parameter body saved-env)
                       (set! exp-or-proc-reg body)
                       (set! val-or-env-reg
                             (extend-env parameter val-or-env-reg saved-env))
                       (set! selector 'value-of/k))))
                  ((apply-cont)
                   (cases continuation cont-reg
                     (end-cont ()
                       (eopl:printf "End of computation.~%")
                       (set! selector 'done))
                     (diff1-cont (subtrahend env saved-cont)
                       (set! cont-reg (diff2-cont val-or-env-reg saved-cont))
                       (set! exp-or-proc-reg subtrahend)
                       (set! val-or-env-reg env)
                       (set! selector 'value-of/k))
                     (diff2-cont (minuend-value saved-cont)
                       (set! cont-reg saved-cont)
                       (set! val-or-env-reg
                             (num-val (- (expval->num minuend-value)
                                         (expval->num val-or-env-reg)))))
                     (zero1-cont (saved-cont)
                       (set! cont-reg saved-cont)
                       (set! val-or-env-reg
                             (bool-val (zero? (expval->num val-or-env-reg)))))
                     (if-test-cont (consequent alternative env saved-cont)
                       (set! cont-reg saved-cont)
                       (if (expval->bool val-or-env-reg)
                           (set! exp-or-proc-reg consequent)
                           (set! exp-or-proc-reg alternative))
                       (set! val-or-env-reg env)
                       (set! selector 'value-of/k))
                     (let-exp-cont (bound-var body env saved-cont)
                       (set! cont-reg saved-cont)
                       (set! exp-or-proc-reg body)
                       (set! val-or-env-reg
                             (extend-env bound-var val-or-env-reg env))
                       (set! selector 'value-of/k))
                     (rator-cont (operand env saved-cont)
                       (set! cont-reg (rand-cont val-or-env-reg saved-cont))
                       (set! exp-or-proc-reg operand)
                       (set! val-or-env-reg env)
                       (set! selector 'value-of/k))
                     (rand-cont (operator-value saved-cont)
                       (set! cont-reg saved-cont)
                       (set! exp-or-proc-reg (expval->proc operator-value))
                       (set! selector 'apply-procedure/k)))))))))))))

;;; As mentioned above,
;;; the procedure definitions are derived from
;;; the work of Friedman and Wand,
;;; who published them on Mitchell Wand's Github site,
;;; as part of the repository https://github.com/mwand/eopl3,
;;; under the Creative Commons Attribution-Noncommercial 3.0 Unported License.

;;; The port to R7RS Scheme is copyright (C) 2009, 2015, 2019 by John David Stone
;;; and is likewise released
;;; under the Creative Commons Attribution-Noncommercial 3.0 Unported License.
