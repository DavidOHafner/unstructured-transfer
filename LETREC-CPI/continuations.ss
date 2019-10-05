#!r7rs

;;; Continuations for the continuation-passing LETREC interpreter

;;; John David Stone
;;; Department of Computer Science
;;; Grinnell College
;;; stone@cs.grinnell.edu

;;; Edited by Samantha Hafner

;;; created March 3, 2009
;;; last revised October 4, 2019

;;; This module defines a data type
;;; for continuations in the LETREC programming language,
;;; as described in section 5.1 of
;;; _Essentials of programming languages_, third edition
;;; (Cambridge, Massachusetts: The MIT Press, 2008; ISBN 978-0-262-06279-4),
;;; by Daniel P. Friedman and Mitchell Wand.

;;; Extention to add lists as an expressed value are by
;;; Samantha Orion Hafner according to specifications by
;;; John David Stone. All code changes noted.

(define-library (LETREC-CPI continuations)
  (export continuation? end-cont diff1-cont diff2-cont zero1-cont if-test-cont
          let-exp-cont rator-cont rand-cont
          cons1-cont cons2-cont null?1-cont car1-cont cdr1-cont);CHANGED to export 5 new continuations
  (import (scheme base)
          (utilities eopl)
          (LETREC syntax-trees)
          (LETREC expvals-and-environments))
  (begin

    (define-datatype continuation continuation?
      (end-cont)
      (diff1-cont (subtrahend expression?)
                  (env environment?)
                  (saved-cont continuation?))
      (diff2-cont (minuend-value expval?)
                  (saved-cont continuation?))
      (zero1-cont (saved-cont continuation?))
      (if-test-cont (consequent expression?)
                    (alternative expression?)
                    (env environment?)
                    (saved-cont continuation?))
      (let-exp-cont (bound-var identifier?)
                    (body expression?)
                    (env environment?)
                    (saved-cont continuation?))
      (rator-cont (operand expression?)
                  (env environment?)
                  (saved-cont continuation?));CHANGED to export 5 new continuations
      (rand-cont (operator-value expval?)
                 (saved-cont continuation?))
      (cons1-cont (cdr-expression expression?)
                  (env environment?)
                  (saved-cont continuation?))
      (cons2-cont (car-value expval?)
                  (saved-cont continuation?))
      (null?1-cont (saved-cont continuation?))
      (car1-cont (saved-cont continuation?))
      (cdr1-cont (saved-cont continuation?)))));end CHANGE

;;; This definition is derived from the work
;;; of Friedman and Wand, who made their versions available at
;;; http://www.eopl3.com/code.html under the Creative Commons
;;; Attribution-Noncommercial 3.0 Unported license
;;; (http://creativecommons.org/licenses/by-nc/3.0/).

;;; The modified code presented here
;;; is copyright (C) 2009, 2015, 2019 by John David Stone
;;; and is likewise released
;;; under the Creative Commons Attribution-Noncommercial 3.0 Unported license.

;;; The extention to add lists as an expressed value and coresponding tests, if any,
;;; are copytight (C) 2019 by Samantha Orion Hafner and are likewise released
;;; under the Creative Commons Attribution-Noncommercial 3.0 Unported License.