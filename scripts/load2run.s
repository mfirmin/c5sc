SCRIPTS runonce.s;

BEGINSCRIPT run(void)

PHASE 0
LOAD runstart.sav;
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> runonce.s(void);
TRANSITION to(-1).after(iterations 10);
ENDPHASE
ENDSCRIPT
