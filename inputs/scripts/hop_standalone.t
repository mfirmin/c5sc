SCRIPTS hop.t, stand.t;

BEGINSCRIPT hop(void)

PHASE 0
> stand.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> hop.t(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
