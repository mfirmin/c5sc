SCRIPTS simbicon2phase.t;

BEGINSCRIPT run(void)
PHASE 0
> simbicon2phase.t(.2, 0.0, 0.0, -.2, -.2, 0.14, -1.08, 2.18, 0.05, -.2, -.27);
TRANSITION to(-1).after(complete);
ENDPHASE
ENDSCRIPT
