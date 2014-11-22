SCRIPTS simbiconfbonce.t, simbicononce.t;

BEGINSCRIPT walk(void)
PHASE 0
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbicononce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2);
TRANSITION to(1).after(iterations 5);
ENDPHASE

PHASE 1
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbiconfbonce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2, 1., 500);
TRANSITION to(2).after(iterations 3);
ENDPHASE

PHASE 2
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbiconfbonce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2, 0.7, 500);
TRANSITION to(3).after(iterations 2);
ENDPHASE

PHASE 3
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbiconfbonce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2, 0.5, 500);
TRANSITION to(4).after(iterations 2);
ENDPHASE

PHASE 4
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbiconfbonce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2, 0.3, 500);
TRANSITION to(-1).after(iterations 5);
ENDPHASE

ENDSCRIPT
