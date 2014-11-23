SCRIPTS balance2ankle.t;

BEGINSCRIPT grav(void)

PHASE 0
> balance2ankle.t(0);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
	POSE rShoulder(-1.57), rElbow(0.0), rWrist(0.0, 5.0, 3.0);
ENDACTIONS
TRANSITION to(2).after(time 1);
ENDPHASE

PHASE 2
ACTIONS
	POSE rWrist(0.0,0.0,0.0), rShoulder(0.0,0.0,0.0), rElbow(0.0,0.0,0.0);
ENDACTIONS
TRANSITION to(3).after(time 0);
ENDPHASE

PHASE 3
ACTIONS
	GC rHand.by(rShoulder);
ENDACTIONS
TRANSITION to(3).after(time 500);
ENDPHASE



ENDSCRIPT

