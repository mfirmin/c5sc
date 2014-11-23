SCRIPTS standVFFB.t, squatVFFB.t;

BEGINSCRIPT tests2s(void)

PHASE 0
> standVFFB.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> squatVFFB.t(2);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
