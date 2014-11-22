SCRIPTS standVFFB.t;

BEGINSCRIPT standForever(void)

PHASE 0
> standVFFB.t(5, 5);
TRANSITION to(0).after(complete);
ENDPHASE

ENDSCRIPT
