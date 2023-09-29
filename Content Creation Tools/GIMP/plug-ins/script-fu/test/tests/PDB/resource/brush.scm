; Test methods of Brush subclass of Resource class

; !!! See also resource.scm

; !!! Testing depends on a fresh install of GIMP.
; A prior testing failure may leave brushes in GIMP.
; The existing brush may have the same name as hard coded in tests.
; In future, will be possible to create new brush with same name as existing?


;      new


; new succeeds
; setup, not an assert
(define testNewBrush (car (gimp-brush-new "TestBrushNew")))

; a resource is an int ID  in ScriptFu
(assert `(number? ,testNewBrush))

; new returns brush of given name
; note call superclass method
(assert `(string=?
            (car (gimp-resource-get-name ,testNewBrush))
            "TestBrushNew"))



;               attributes of new brush

; new brush is kind generated versus raster
(assert `(= (car (gimp-brush-is-generated ,testNewBrush))
            1))

; angle     default is 0
(assert `(=
            (car (gimp-brush-get-angle ,testNewBrush))
            0))

; aspect-ratio   default  is 1.0
; FIXME: the doc says 0.0
(assert `(=
            (car (gimp-brush-get-aspect-ratio ,testNewBrush))
            1.0))

; hardness   default is 0.5
; FIXME: the doc says 0
(assert `(=
            (car (gimp-brush-get-hardness ,testNewBrush))
            0.5))

; shape default is GENERATED-CIRCLE
(assert `(=
            (car (gimp-brush-get-shape ,testNewBrush))
            BRUSH-GENERATED-CIRCLE))

; spikes default is 2
; FIXME: docs says 0
(assert `(=
            (car (gimp-brush-get-spikes ,testNewBrush))
            2))

; get-radius    default 5.0
; FIXME: docs says 0
(assert `(=
            (car (gimp-brush-get-radius ,testNewBrush))
            5.0))


; spacing default 20
; FIXME: docs says 0
(assert `(=
            (car (gimp-brush-get-spacing ,testNewBrush))
            20))

; get-info returns a list of attributes
; For generated, color bytes is zero
(assert `(equal? (gimp-brush-get-info ,testNewBrush)
                `(11 11 1 0)))

; get-pixels returns a list of attributes
; It is is long so we don't compare.
; This test is just that it doesn't crash or return #f.
(assert `(gimp-brush-get-pixels ,testNewBrush))



;              delete

; can delete a new brush
; PDB returns void, ScriptFu returns wrapped truth i.e. (#t)
(assert `(car (gimp-resource-delete ,testNewBrush)))

; delete was effective
; ID is now invalid
(assert `(= (car (gimp-resource-id-is-valid ,testNewBrush))
            0))



;       Kind non-generated brush

; Brush named "z Pepper" is non-generated and is a system brush always installed

; setup, not an assert
(define testNongenBrush (car (gimp-resource-get-by-name "GimpBrush" "z Pepper")))

; brush says itself is not generated



;       Certain attributes of non-generated brush yield errors
; angle, aspect-ratio, hardness, shape, spikes, radius


; angle is not an attribute of non-generated brush
(assert-error
  `(gimp-brush-get-angle ,testNongenBrush)
  "Procedure execution of gimp-brush-get-angle failed")

; TODO all the other attributes


;        Non-generated brush attributes

; is not generated
(assert `(=
            (car (gimp-brush-is-generated ,testNongenBrush))
            0))

; spacing
(assert `(=
            (car (gimp-brush-get-spacing ,testNongenBrush))
            100))

; pixels returns a list of attributes
; FAIL: CRASH Inconsistency detected by ld.so: dl-runtime.c: 63: _dl_fixup: Assertion `ELFW(R_TYPE)(reloc->r_info) == ELF_MACHINE_JMP_SLOT' failed!
; Known to fail because TS allocation of 120k byte contiguous cells for vector fails.
; (assert `(gimp-brush-get-pixels ,testNongenBrush))

; get-info returns a list of attributes
(assert `(equal? (gimp-brush-get-info ,testNongenBrush)
                `(180 220 1 3)))



;                miscellaneous

; gimp-brush-get-by-name returns error, when brush of that name not exists
(assert-error '(gimp-brush-get-by-name "foo")
              "Procedure execution of gimp-brush-get-by-name failed on invalid input arguments: Brush 'foo' not found")
