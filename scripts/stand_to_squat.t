
SCRIPTS standVFFB.t, balance2ankle.t, squatVFFB.t;

BEGINSCRIPT STAND_TO_SQUAT(void)

PHASE 0
> standVFFB.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
TRANSITION to(2).after(stable);
ENDPHASE

PHASE 2 # start to squat
> squatVFFB.t(0);
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 3
ACTIONS
	VFFB uTorso(2000., 1000.).by(rAnkle);
	VFFB uTorso(2000., 1000.).by(lAnkle);
ENDACTIONS
TRANSITION to(-1).after(stable);
ENDPHASE
ENDSCRIPT
