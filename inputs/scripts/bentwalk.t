SCRIPTS simbicon.t;

BEGINSCRIPT bentwalk(void)
PHASE 0
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbicon.t(.3, 0.0, -0.05, -.1, 0.0, 0.6, -.8,   .1,  1.1,  .05,  0.05, 0.1,  0.0);
TRANSITION to(-1).after(complete);
ENDPHASE
ENDSCRIPT
