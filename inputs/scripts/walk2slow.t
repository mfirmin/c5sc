SCRIPTS walkonce.t, walkspeeds.t;

BEGINSCRIPT walk2slow(void)

PHASE 0
> walkonce.t(void);
TRANSITION to(1).after(iterations 2);
ENDPHASE

PHASE 1
> walkspeeds.t(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
