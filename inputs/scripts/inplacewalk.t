SCRIPTS simbicon.t;

BEGINSCRIPT walk(void)
PHASE 0
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbicon.t(.3, 0.0, -1.55, -.4, 0.0, -0., -.62,   .1,  1.1,  .05,  0.05, 0.1,  -.082);
TRANSITION to(-1).after(complete);
ENDPHASE
ENDSCRIPT
