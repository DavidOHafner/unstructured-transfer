#!r7rs

;;; Tokens in TYPED-OO

;;; John David Stone
;;; Department of Computer Science
;;; Grinnell College

;;; created April 28, 2009
;;; last revised October 11, 2019

;;; This library defines a data type
;;; for lexical tokens of the TYPED-OO programming language,
;;; as described in section 9.5 of
;;; _Essentials of programming languages_, third edition
;;; (Cambridge, Massachusetts: The MIT Press, 2008; ISBN 978-0-262-06279-4),
;;; by Daniel P. Friedman and Mitchell Wand.

;;; TYPED-OO has tokens of forty-six kinds:
;;; "numbers" (actually, numerals),
;;; identifiers, minus signs, open- and close-parentheses,
;;; commas, equals signs, semicolons, plus signs, asterisks,
;;; arrows, colons, underscores,
;;; and the keywords zero?, if, then, else, let, in, proc, letrec, set,
;;; begin, end, cons, car, cdr, null?, emptylist, list,
;;; class, extends, field, method, new, send, super, self,
;;; int, bool, implements, interface, cast, instanceof, void, and listof.

(define-library (TYPED-OO tokens)
  (export token? numeral-token minus-sign open-parenthesis comma
          close-parenthesis zero?-token if-token then-token else-token
          identifier-token let-token equals-sign in-token proc-token
          letrec-token set-token begin-token semicolon end-token plus-sign
          asterisk cons-token car-token cdr-token null?-token emptylist-token
          list-token class-token extends-token field-token method-token
          new-token send-token super-token self-token int-token bool-token
          arrow colon implements-token interface-token cast-token
          instanceof-token void-token listof-token underscore)
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
      (set-token)
      (begin-token)
      (semicolon)
      (end-token)
      (plus-sign)
      (asterisk)
      (cons-token)
      (car-token)
      (cdr-token)
      (null?-token)
      (emptylist-token)
      (list-token)
      (class-token)
      (extends-token)
      (field-token)
      (method-token)
      (new-token)
      (send-token)
      (super-token)
      (self-token)
      (int-token)
      (bool-token)
      (arrow)
      (colon)
      (implements-token)
      (interface-token)
      (cast-token)
      (instanceof-token)
      (void-token)
      (listof-token)
      (underscore))))

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