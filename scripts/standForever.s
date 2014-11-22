SCRIPTS standVFFB.t;

BEGINSCRIPT standForever(void)

PHASE 0
> standVFFB.t(50, 50);
TRANSITION to(-1).after(fallen x .6);
TRANSITION to(0).after(complete);
ENDPHASE

ENDSCRIPT
