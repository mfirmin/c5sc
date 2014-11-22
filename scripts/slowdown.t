SCRIPTS balance2ankle.t, walkspeeds.t, balancecop.t, walk2stop.t;

BEGINSCRIPT slowdown(void)

PHASE 0
> balance2ankle.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> walkspeeds.t(1.3, 3);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> walkspeeds.t(1.2, 3);
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 3
> walkspeeds.t(1.1, 3);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 4
> walkspeeds.t(1., 3);
TRANSITION to(5).after(complete);
ENDPHASE

PHASE 5
> walkspeeds.t(.9, 3);
TRANSITION to(6).after(complete);
ENDPHASE

PHASE 6
> walkspeeds.t(.8, 3);
TRANSITION to(7).after(complete);
ENDPHASE

PHASE 7
> walkspeeds.t(.7, 3);
TRANSITION to(8).after(complete);
ENDPHASE

PHASE 8
> walkspeeds.t(.6, 3);
TRANSITION to(9).after(complete);
ENDPHASE

PHASE 9
> walkspeeds.t(.5, 3);
TRANSITION to(10).after(complete);
ENDPHASE

PHASE 10
> walkspeeds.t(.4, 3);
TRANSITION to(11).after(complete);
ENDPHASE

PHASE 11
> walkspeeds.t(.3, 3);
TRANSITION to(12).after(complete);
ENDPHASE

PHASE 12
> walk2stop.t(void);
TRANSITION to(-1).after(stable);
ENDPHASE

ENDSCRIPT
