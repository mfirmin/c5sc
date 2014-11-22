SCRIPTS standVFFB.t;

BEGINSCRIPT tester(void)

PHASE 0
> standVFFB.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ENVACTIONS
    toggleVisible(STAIRCASE);
    toggleCollidable(STAIRCASE);
ENDACTIONS
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> standVFFB.t(2);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
