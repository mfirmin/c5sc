SCRIPTS simbiconfbonce.t, simbicononce.t, walk2stop.t;

BEGINSCRIPT walk(void)
PHASE 0
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbicononce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2);
TRANSITION to(1).after(iterations 1);
ENDPHASE

PHASE 1
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbiconfbonce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2, 1., 500);
TRANSITION to(2).after(iterations 1);
ENDPHASE

PHASE 2
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbiconfbonce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2, 0.7, 500);
TRANSITION to(3).after(iterations 1);
ENDPHASE

PHASE 3
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbiconfbonce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2, 0.5, 500);
TRANSITION to(4).after(iterations 1);
ENDPHASE

PHASE 4
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbiconfbonce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2, 0.3, 500);
TRANSITION to(5).after(iterations 1);
ENDPHASE

PHASE 5
#           (dt, cde, cdo,  cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)
> simbiconfbonce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2, 0.15, 200);
TRANSITION to(6).after(iterations 3);
ENDPHASE

PHASE 6
> walk2stop.t(0.0, 0);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
