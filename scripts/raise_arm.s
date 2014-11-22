SCRIPTS standVFFB.t;

BEGINSCRIPT raise_arm(void)

PHASE 0
> standVFFB.t(2);
TRANSITION to(1).after(complete);
ENDPHASE


PHASE 1
ACTIONS
	VFFB uTorso(2000., 250.).by(rAnkle).over(cop);
	VFFB uTorso(2000., 250.).by(lAnkle).over(cop);
    VF (500,2000,0).on(rHand).by(rShoulder);
ENDACTIONS
TRANSITION to(-1).after(time 500);

ENDPHASE

ENDSCRIPT
