SCRIPTS simbicon.t;

BEGINSCRIPT walk(void)
PHASE 0
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbicon.t(.2, 0.0, -2., -.2, 0.0, -0.0, -1.,   .7,  2.2,  .05,  0.05, 0.1,  -.2);
TRANSITION to(-1).after(complete);
ENDPHASE
ENDSCRIPT
