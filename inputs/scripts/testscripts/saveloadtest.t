SCRIPTS standVFFB.t, squatVFFB.t;

BEGINSCRIPT saveload(void)

PHASE 0
> standVFFB.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
TRANSITION to(2).after(stable);
ENDPHASE

PHASE 2
SAVE save1.state;
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 3 # start to squat
> squatVFFB.t(0);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 4
ACTIONS
	VFFB uTorso(2000., 1000.).by(rAnkle);
	VFFB uTorso(2000., 1000.).by(lAnkle);
ENDACTIONS
TRANSITION to(5).after(stable);
ENDPHASE

PHASE 5
LOAD save1.state;
TRANSITION to(3).after(complete);
ENDPHASE

ENDSCRIPT

