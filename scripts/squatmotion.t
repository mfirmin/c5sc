SCRIPTS squat.t, rise.t;

BEGINSCRIPT squatrise(void)
PHASE 0
> squat.t(void);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> rise.t(void);
TRANSITION to(-1).after(complete);
ENDPHASE
ENDSCRIPT
