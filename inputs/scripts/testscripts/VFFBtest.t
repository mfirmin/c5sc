SCRIPTS stand.t, squatVFFB.t, standVFFB.t;


BEGINSCRIPT VFFBtest(void)

PHASE 0
> stand.t(.3);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> squatVFFB.t(2);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> standVFFB.t(1.5);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT

