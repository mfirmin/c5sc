SCRIPTS standVFFB.t, walk2times.s;

BEGINSCRIPT stand2walk(void)

PHASE 0
LOAD walkstate.sav;
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbicononce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2);
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 3
> simbicononce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 4
TRANSITION to(5).after(complete);
ENDPHASE

PHASE 5
> simbicononce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2);
TRANSITION to(6).after(iterations 4);
ENDPHASE

PHASE 6
TRANSITION to(-1).after(complete);
ENDPHASE



ENDSCRIPT
