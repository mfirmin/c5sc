SCRIPTS step_up.t;

BEGINSCRIPT stairclimb(void)

PHASE 0
> step_up.t(.25, .3);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> step_up.t(.5, .5);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> step_up.t(.75, .7);
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 3
> step_up.t(1., .9);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
