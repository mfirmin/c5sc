SCRIPTS stand.t, walkonce.t, walk2stop.t, step.t, balance2ankle.t, walkbackwardonce.t, fastwalkonce.t, runonce.t;

BEGINSCRIPT keyboard(void)
PHASE 0
> balance2ankle.t(0);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
TRANSITION to(6).after(press A);
TRANSITION to(2).after(press D);
ENDPHASE

PHASE 2
> walkonce.t(void);
TRANSITION to(4).after(release D);
TRANSITION to(3).after(press Q);
ENDPHASE

PHASE 3
> fastwalkonce.t(void);
TRANSITION to(2).after(release Q);
TRANSITION to(2).after(release D);
TRANSITION to(7).after(iterations 5);
ENDPHASE

PHASE 4
> walk2stop.t(void);
TRANSITION to(0).after(complete);
ENDPHASE

PHASE 5
> step.t(void);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 6
> walkbackwardonce.t(void);
TRANSITION to(4).after(press D);
ENDPHASE

PHASE 7
> runonce.t(void);
TRANSITION to(3).after(release Q);
TRANSITION to(3).after(release D);
ENDPHASE


ENDSCRIPT
