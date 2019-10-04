#!r7rs

;;; Tokens in LETREC

;;; John David Stone
;;; Department of Computer Science
;;; Grinnell College

;;; Edited by Samantha Hafner

;;; created February 8, 2009
;;; last revised October 4, 2019

;;; This library defines a data type
;;; for lexical tokens of the LETREC programming language,
;;; as described in section 3.4 of
;;; _Essentials of programming languages_, third edition
;;; (Cambridge, Massachusetts: The MIT Press, 2008; ISBN 978-0-262-06279-4),
;;; by Daniel P. Friedman and Mitchell Wand.

;;; Extention to add lists as an expressed value are by
;;; Samantha Orion Hafner according to specifications by
;;; John David Stone. All code changes noted.

;;; this version of LETREC has tokens of twenty kinds:
;;; "numbers" (actually, numerals),
;;; identifiers, minus signs, open- and close-parentheses,
;;; commas, equals signs,
;;; and the keywords zero?, if, then, else, let, in, proc, letrec, emptylist, cons, null?, car, cdr.

(define-library (LETREC tokens)
  (export token? numeral-token minus-sign open-parenthesis comma
          close-parenthesis zero?-token if-token then-token else-token
          identifier-token let-token equals-sign in-token proc-token letrec-token
          emptylist-token cons-token null?-token car-token cdr-token);CHANGE to export new tokens
  (import (scheme base)
          (utilities eopl))
  (begin

    ;; A single define-datatype declaration
    ;; accommodates all of these tokens as variants.

    (define-datatype token token?
      (numeral-token (value exact-integer?))
      (minus-sign)
      (open-parenthesis)
      (comma)
      (close-parenthesis)
      (zero?-token)
      (if-token)
      (then-token)
      (else-token)
      (identifier-token (id identifier?))
      (let-token)
      (equals-sign)
      (in-token)
      (proc-token)
      (letrec-token)
      (emptylist-token);CHANGE to add five new tokens
      (cons-token)
      (null?-token)
      (car-token)
      (cdr-token))));end CHANGE

;;; Copyright (C) 2009, 2015, 2019  John David Stone

;;; This program is free software.
;;; You may redistribute it and/or modify it
;;; under the terms of the GNU General Public License
;;; as published by the Free Software Foundation -- 
;;; either version 3 of the License,
;;; or (at your option) any later version.

;;; This program is distributed
;;; in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY --
;;; without even the implied warranty
;;; of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
;;; See the GNU General Public License for more details.

;;; You should have received a copy
;;; of the GNU General Public License
;;; along with this program.
;;; If not, it is available on the World Wide Web
;;; at https://www.gnu.org/licenses/gpl.html.

;;; The extention to add lists as an expressed value and coresponding tests, if any,
;;; are copytight (C) 2019 by Samantha Orion Hafner and are likewise released
;;; under the Creative Commons Attribution-Noncommercial 3.0 Unported License.