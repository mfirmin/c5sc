SCRIPTS simbicon2phaseonce.t;

BEGINSCRIPT run(void)
PHASE 0
> simbicon2phaseonce.t(.2, 0.0, 0.0, -.2, -.2, 0.14, -1.08, 2.18, 0.05, -.2, -.27).atPhase(1);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> simbicon2phaseonce.t(.2, 0.0, 0.0, -.2, -.2, 0.14, -1.08, 2.18, 0.05, -.2, -.27);
TRANSITION to(2).after(iterations 9);
ENDPHASE

PHASE 2
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
