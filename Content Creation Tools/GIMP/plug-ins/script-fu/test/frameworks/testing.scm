; A testing framework
;
; Independent of GIMP except for gimp_message,
; which you can redefine


; Testing language

; AssertStmt      ~ (assert '(<code>))
; AssertErrorStmt ~ (assert-error '(<code>)  <prefix of expected error string>)
; ReportStmt      ~ (testing:report)
; LoadStmt        ~ (testing:load-test <filename>)
; AllPassedPredicate ~ (testing:all-passed?)
;
; AssertStmt and AssertErrorStmt have side effects on the testing state,
; and the other statements yield or display the state.
;
; AssertStmt and AssertErrorStmt also have side effects on the display,
; displaying failures.
;
; AssertStmt and AssertErrorStmt also yield #t or #f
; meaning pass or fail.


; Syntax errors

; The test framework WILL NOT handle syntax errors.
; The quoted code under tests must parse without syntax errors.
; Some errors that TinyScheme throws ARE syntax errors, but not named such.
; For example '#\xzzz is a syntax error (z is not a hex digit).
; Thus the test framework won't handle '#\xzzz .


; Algebra of calls
;
; Typically one or more AssertStmt followed by a ReportStmt
; when viewed in the console.
; Or one or more AssertStmt followed by AllPassedPredicate
; to yield an overall testing result,
; when testing is automated.

; Testing error messages
;
; Error messages may have details such as line number of error
; that may change over time.
; Testing expects that details will be a suffix of the error message.
; Passing is measured by comparing given expected prefix of error
; with actual error message.


; Notes on implementation:
;
; Debug stream for testing is gimp-message


; EvalResult object
; is-a tuple (result, error)
; <result> is dynamic type returned by eval
; <error> is type string

(define (make-evalresult result errors)
  ;(gimp-message "make-evalresult")
  (list result errors))
(define (evalresult-get-result x) (car x))
(define (evalresult-get-error x)  (cadr x))
(define (evalresult-has-no-error? x)
   (= (string-length (cadr x)) 0))


;    state

(define testing:passed 0)  ; counter
(define testing:failed '())  ; list

(define (testing:reset!)
  (set! testing:passed 0)
  (set! testing:failed   '()))

(define (testing:log-passed!)
  ; Not announce success to console, but can debug
  (gimp-message "Passed")
  (set! testing:passed (+ testing:passed 1)))

; log any failure
(define (testing:log-fail! failure-string)
  ; Announce fail as it happens
  (displayln "")
  (display "Failed: ")
  (displayln failure-string)
  ; save in state: prepend to list of failures
  (set! testing:failed
        (cons failure-string
              testing:failed)))


(define (testing:log-fail-assert! code eval-result)
  (testing:log-fail! (testing:format-fail-assert code eval-result)))

(define (testing:log-fail-assert-error! code actual-error expected-error)
  (testing:log-fail! (testing:format-fail-assert-error
                 code
                 actual-error
                 expected-error)))

; reset testing state when test framework is loaded
(testing:reset!)



;   reporting
; These methods encapsulate formatting of strings and reports

; A report is a summary of counts
; followed by line for each failure
(define (testing:report)
    (testing:display-summary)
    (testing:display-fails))

(define (testing:display-summary)
  (displayln "")
  (display "Passed: ")
  (display testing:passed)
  (display "   Failed: ")
  (displayln (length testing:failed)))

; Display list of failures in time order
; This does not iterate over the list.
; It relies on newlines in the individual failure formats.
(define (testing:display-fails)
  (if (> (length testing:failed) 0)
      (begin
        (displayln "Failures:")
        ; reverse list so it displays in time order
        (display (reverse testing:failed)))
      '()))

; returns a string for failed assert-error
; Of form: Code: foo Actual: bar Expected: zed
(define (testing:format-fail-assert-error code actual-error expected-error)
  (string-append
    "<Code> "
    (any->string code)
    (string #\newline)
    " <Actual> "
    actual-error
    (string #\newline)
    " <Expected> "
    expected-error
    (string #\newline)
    (string #\newline))
)

; returns a string for failed assert
; Of form    Code: foo Error: bar
(define (testing:format-fail-assert code eval-result)
  (string-append
    "<Code>"
    (any->string code)
    (string #\newline)
    ; Any error message.
    "<Error>"
    (evalresult-get-error eval-result)
    (string #\newline)
    (string #\newline)
    ; We don't display result, it must be false
    ; because were given a boolean proposition
    )
)


;   boolean result for entire testing session

(define (testing:all-passed? )
  (not (= (length testing:failed) 0)))



; Record eval-result, a tuple, from eval of code.
; This knows that a passed normal test has true result and empty error.
; <code is> a an object? a Scheme text, is a boolean proposition,
(define (testing:record-assert-result eval-result code)
  ;(gimp-message "record-assert-result")
  ; passed when has no error and result is #t
  (if (and (evalresult-has-no-error? eval-result)
           (evalresult-get-result eval-result))
      (testing:log-passed!)
      ; fail
      (testing:log-fail-assert!
        code
        eval-result)))

; Record eval-result, a tuple, from eval of code.
; This knows that a passed assert-error test has don't care result.
; Instead, this knows the test passes if given <expected-error>
; matches a prefix of the actual error message yielded by eval.
; <result> is dynamic type returned by eval
; <error-message> is type string
; <code> is a an object? a Scheme text, is a boolean proposition.
; <expected-error> is type string
(define (testing:record-assert-error-result eval-result code expected-error)
  ; debug
  ;(displayln "record-assert-error-result")
  ;(displayln eval-result)

  ; expected error string a prefix of actual error string?
  (if (string-prefix?
        expected-error
        (evalresult-get-error eval-result))
      ; passed
      (begin
        (testing:log-passed!)
        #t)
      ; fail, pass asserted code, actual error, expected error
      (begin
        (testing:log-fail-assert-error!
          code
          (evalresult-get-error eval-result)
          expected-error)
        #f)))

; Strict equality of error strings:
;(if (equal?
;        (evalresult-get-error eval-result)
;        expected-error)


; Statments in the testing DSL.

; The usual or normal test.
; <code> is a boolean proposition expected to yield #t
(define (assert code)
  (let* ((eval-result (harnessed-eval code)))
    ; eval-result is tuple
    ; record normal result i.e. error not expected
    (testing:record-assert-result
      eval-result
      code)
    ; Statements have side-effect on testing state,
    ; but also return boolean result of predicate.
    (evalresult-get-result eval-result )))

; A test of abnormality.
; <code> is not expected to yield any particular value
; <error> is a prefix of error string that <code> is expected to throw.
(define (assert-error code expected-error)
  (let* ((eval-result (harnessed-eval code)))
    ; eval-result is tuple
    ; record normal result i.e. error not expected
    (testing:record-assert-error-result
      eval-result
      code
      expected-error)
    ; Returns whether error matches expected error prefix.
    ))


; eval code, returning tuple of result and errors
; This knows how to capture errors
; but not what result and errors mean for testing.
; Harnessed means: surrounded by code to capture error messages.
;
; Assert the pre-condition *error-hook* is (throw msg) see script-fu.init.
; So any call (error msg) is (throw msg)
; But we are not using (catch handler code).
; We are only overriding *error-hook*
;
; Any given eval of code under test may yield many calls to the error hook.
; We only record the first error message in an eval of the code under test.

(define (harnessed-eval code)
  ;(gimp-message "harnessed-eval")
  (let* ((old-error-hook *error-hook*) ; save original handler, which is throw
         (errors "") ; initial empty string
         (result #f) ; initial result is #f, not () which is truthy

         (testing-error-hook
           (lambda (xs)
             ;(gimp-message "testing-error-hook")

             ; Only record the first error
             (if (= (string-length errors) 0)
                 (if (string? xs)
                    (begin
                      ;(gimp-message "xs is string")
                      (set! errors xs))
                    (set! errors "Non-string error")))

             ; Do not chain up to old handler: (old-error-hook xs)
             ; Old handler is usually throw, which is error,
             ; and that infinite loops
             ;
             ; This returns to current eval,
             ; which may call this error hook again.
             ;(gimp-message "returning from error hook")
             )))
    ;(gimp-message "override error hook")
    (set! *error-hook* testing-error-hook)
    ;(gimp-message "eval test code")
    (set! result (eval code))
    ;(gimp-message "restore error hook")
    ; restore the error hook for any code in a test script between asserts
    (set! *error-hook* old-error-hook)
    ; return an EvalResult
    (make-evalresult result errors)))





;    port utility


(define (with-string open-function str function)
  (let ((port (open-function str)))
    (if (port? port)
      (let ((result '()))
        (set! result (function port))
        (close-port port)
        result)
      ; Testing internal error.  Hijack the testing framework
      (testing:log-fail! "Failed to open string for string port!" '() ))))

(define (call-with-output-string str function)
  (with-string open-output-string str function))



;   string utility

(define (trim char chars)
  (if (= (char->integer char) (char->integer (car chars)))
      (trim char (cdr chars))
      chars))

(define (rtrim str)
  (list->string (reverse (trim #\space (reverse (string->list str))))))

; any is code
; Not using atom->string.  Using write
(define (any->string any)
  (let* ((to-string
           (lambda (any)
             (let* ((str (make-string 256)))
               (call-with-output-string str
                 (lambda (port) (write any port)))
               str))))
    (rtrim (to-string any))))


; string-prefix? is in R5RS but not tinyscheme.
; string-prefix? is in various SRFI's but we don't have them here
; So yet again, we need to implement it de novo
(define (string-prefix? str1 str2)
  ; if str1 is longer than str2, it is not a prefix
  (if (> (string-length str1) (string-length str2))
    #f
    ; else str2 is longer str2 than str1.
    ; str1 is a prefix if the leading substring of str2,
    ; that is the length of str1, equals str1.
    (string=?
      str1
      (substring str2 0 (string-length str1)))))



;     filesystem utility

; Return the fullpath of a test script.
; When fileScm is empty, returns path to dir of test scripts.
; From gimp-data-directory i.e. the shared install dir for GIMP
; Require filename is string
; Require suffix, usually ".scm" on the filename

(define (path-to-test-scripts fileScm)
    (let*   (   (path (string-append gimp-data-directory DIR-SEPARATOR "tests")))
        (if (zero? (string-length fileScm)) path (string-append path DIR-SEPARATOR fileScm))))

(define (path-to-test-images fileScm)
    (let*   (   (path (string-append gimp-data-directory DIR-SEPARATOR "images")))
        (if (zero? (string-length fileScm)) path (string-append path DIR-SEPARATOR fileScm))))

; load a test file, which executes it
; Knows where GIMP installs test scripts
;
; Subsequently, testing:report will say results
(define (testing:load-test filename)
  (gimp-message (path-to-test-scripts filename))
  (load (path-to-test-scripts filename)))

; Tell Gimp to load a test image
; Returns ID of image
; Knows installed image directory (not dedicated to testing but always there.)
; Accepts image suffixes that Gimp can load.
; Typical is /usr/local/share/gimp/2.99/images/wilber.png
(define (testing:load-test-image filename)
  (gimp-message (path-to-test-images filename))
  ; unpack ID via car
  (car (gimp-file-load RUN-NONINTERACTIVE (path-to-test-images filename))))
