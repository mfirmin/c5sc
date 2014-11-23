SCRIPTS standVFFB.t, somersault.t;

BEGINSCRIPT s2somersault(void)

PHASE 0
> standVFFB.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> somersault.t(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
