SCRIPTS walkonce.s, simbiconfbonce.t, walk2stop.t, standForever.s;

BEGINSCRIPT testPass(void)

PHASE 0
ENVACTIONS
    toggleCollidable(CHAIR);
ENDACTIONS
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> simbiconfbonce.t(.3, 0.0, -2.2, -.2, 0.0, 0.0, -.4,   .7,  1.1,  .05,  0.05, 0.1,  -.2, 0.15, 200);
TRANSITION to(2).after(pass CHAIR .3);
ENDPHASE

PHASE 2
ENVACTIONS
    toggleCollidable(CHAIR);
ENDACTIONS
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 3
> walk2stop.t(void);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 4
> standForever.s(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
