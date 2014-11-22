SCRIPTS walkonce.s, fastwalkonce.s, runonce.s;

BEGINSCRIPT walk(void)
PHASE 0
> walkonce.s(void);
TRANSITION to(1).after(iterations 2.);
ENDPHASE

PHASE 1
> fastwalkonce.s(void);
TRANSITION to(2).after(iterations 2);
ENDPHASE

PHASE 2
> runonce.s(void);
TRANSITION to(3).after(iterations 5);
ENDPHASE

PHASE 3
SAVE runstart.sav;
TRANSITION to(2).after(complete);
ENDPHASE

ENDSCRIPT
