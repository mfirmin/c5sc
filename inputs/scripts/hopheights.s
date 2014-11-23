SCRIPTS fwdhop.s, standVFFB.t;


BEGINSCRIPT hopheights(void)

PHASE 0
    LOAD ontopofstairs.sav;
TRANSITION to(1).after(complete);
ENDPHASE


PHASE 1
> fwdhop.s(void);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 2
> standVFFB.t(1,1);
TRANSITION to(1).after(complete);
ENDPHASE

ENDSCRIPT
