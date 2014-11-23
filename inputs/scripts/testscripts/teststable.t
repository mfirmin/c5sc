SCRIPTS standVFFB.t, squatVFFB.t, squat.t;

BEGINSCRIPT stable(void)

PHASE 0
> standVFFB.t(0);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> squat.t(void);
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 2
> squatVFFB.t(0);
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 3
TRANSITION to(4).after(stable);
ENDPHASE

PHASE 4
> standVFFB.t(10);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT


