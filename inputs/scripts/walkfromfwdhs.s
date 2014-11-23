SCRIPTS fwdhandspring.s, walk.s;

BEGINSCRIPT test(void)

PHASE 0
LOAD fwd2walk.sav;
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> walk.s(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
