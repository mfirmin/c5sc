SCRIPTS fwdhandspring.s, walk.s;

BEGINSCRIPT test(void)

PHASE 0
> fwdhandspring.s(void);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
SAVE fwd2walk.sav;
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> walk.s(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
