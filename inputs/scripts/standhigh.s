SCRIPTS step_up.t, standVFFB.t;

BEGINSCRIPT stairclimb(void)

PHASE 0
LOAD standOnStair.sav;
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> standVFFB.t(5, 5);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
