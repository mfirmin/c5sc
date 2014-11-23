SCRIPTS skip.s, walkonce.s, skiplow.s;

BEGINSCRIPT walk(void)
PHASE 0
> walkonce.s(void);
TRANSITION to(1).after(iterations 3);
ENDPHASE

PHASE 1
> skip.s(void);
TRANSITION to(2).after(iterations 3);
ENDPHASE

PHASE 2
> walkonce.s(void);
TRANSITION to(-1).after(iterations 5);
ENDPHASE

ENDSCRIPT
