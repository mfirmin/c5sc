
SCRIPTS step_up.t, standVFFB.t;

BEGINSCRIPT stairclimb(void)

PHASE 0
> step_up.t(.25, .3);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> standVFFB.t(3, 3);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
