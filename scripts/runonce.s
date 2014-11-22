SCRIPTS simbicon2phaseonce.t;

SET TORQUELIMIT = 370

BEGINSCRIPT run(void)
PHASE 0
> simbicon2phaseonce.t(.2, 0.0, 0.0, -.2, -.2, 0.14, -1.08, 2.18, 0.05, -.2, -.27);
TRANSITION to(-1).after(complete);
ENDPHASE
ENDSCRIPT
