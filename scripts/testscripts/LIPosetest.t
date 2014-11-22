SCRIPTS balance2ankle.t;

BEGINSCRIPT LIPosetest(void)

PHASE 0
> balance2ankle.t(0);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
	LIPOSE rShoulder(-1.5).time(2);
ENDACTIONS
TRANSITION to(2).after(time 2);
ENDPHASE

PHASE 2
ACTIONS
	LIPOSE rShoulder(0.0).time(1);
ENDACTIONS
TRANSITION to(1).after(time 1);
ENDPHASE

ENDSCRIPT
