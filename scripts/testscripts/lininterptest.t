SCRIPTS balance2ankle.t;


BEGINSCRIPT lininterp(void)

PHASE 0
> balance2ankle.t(0);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
	POSE rShoulder(linterp(120.,0.,180.,0.,-3. ) ), lShoulder(-2.);
ENDACTIONS
TRANSITION to(1).after(time 500);
ENDPHASE

ENDSCRIPT

