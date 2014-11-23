SCRIPTS squat.t, balance2ankle.t;

BEGINSCRIPT risetest(void)
PHASE 0
> balance2ankle.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> squat.t(void);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> GC

