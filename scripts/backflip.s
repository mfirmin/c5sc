SCRIPTS standVFFB.t, squatVFFB.t, backflip.t;

SET TORQUELIMIT = 1000

BEGINSCRIPT backflipstandalone(void)
PHASE 0
> standVFFB.t(1, 1);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> squatVFFB.t(2);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> backflip.t(void);
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 3
> standVFFB.t(2, 2);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
