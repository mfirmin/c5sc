# A more natural looking simbicon-style walk.

SCRIPTS simbiconarms.t;

BEGINSCRIPT walk(void)
PHASE 0
#               (dt, cde, cdo,  cve, cvo, tor,   swhe, swho, swke, swko, stke, stko, ankle, lshldf, rshldf, lshldb, rshldb)
> simbiconarms.t(.3, 0.0, -2.2, -.2, 0.0, 0.045, -.4,   .7,  1.0,  .05,  0.05, 0.1,  -.2,   -0.5,   -0.5,   0.5,    0.5);
TRANSITION to(-1).after(complete);
ENDPHASE
ENDSCRIPT
