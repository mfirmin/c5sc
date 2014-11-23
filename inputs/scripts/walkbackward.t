SCRIPTS simbicon.t;

BEGINSCRIPT walk(void)
PHASE 0
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbicon.t(.22, 0.0, -.6, -.28, 0.0, -.2, -.37,  .1,  1.41,  .05,  0.05, 0.1,  -.0);
TRANSITION to(-1).after(complete);
ENDPHASE
ENDSCRIPT
