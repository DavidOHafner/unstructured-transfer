#!r7rs

(import (scheme base)
        (scheme write))

(define midpoint #f)

(let ((counter 0))
  (display "Counter = ")
  (display counter)
  (newline)
  (call-with-current-continuation (lambda (mid)
                                    (set! midpoint mid)))
  (set! counter (+ counter 1))
  (display "Now counter = ")
  (display counter)
  (newline))
