SCRIPTS standVFFB.t, squatVFFB.t;

BEGINSCRIPT standfromsquat(void)

PHASE 0
> squatVFFB.t(1);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> standVFFB.t(1, 1);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
