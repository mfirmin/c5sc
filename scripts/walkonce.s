SCRIPTS simbicononce.t;

BEGINSCRIPT walk(void)
PHASE 0
> simbicononce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4, .7, 1.1, .05, 0.05, 0.1, -.2);
TRANSITION to(-1).after(complete);
ENDPHASE
ENDSCRIPT
