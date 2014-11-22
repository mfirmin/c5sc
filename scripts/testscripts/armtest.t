SCRIPTS balance2ankle.t;


BEGINSCRIPT armtest(angle)

PHASE 0
> balance2ankle.t(0);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
	POSE lShoulder(angle, 300, 100.);
ENDACTIONS
TRANSITION to(-1).after(time 500);
ENDPHASE

ENDSCRIPT
