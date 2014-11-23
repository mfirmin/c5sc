SCRIPTS standVFFB.t, squatVFFB.t;

BEGINSCRIPT primitives(void)

PHASE 0
> standVFFB.t(1,1);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 1
ACTIONS
    POSE rHip(0,0,0);
    POSE lHip(0,0,0);
    POSE lKnee(0,0,0);
    POSE rKnee(0,0,0);
    POSE rAnkle(0,0,0);
    POSE lAnkle(0,0,0);
ENDACTIONS
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
ACTIONS
    VF (-30,300,0).on(uTorso).by(rAnkle);
    VF (-30,300,0).on(uTorso).by(lAnkle);
ENDACTIONS
TRANSITION to(3).after(nocontact rFoot);
ENDPHASE

PHASE 3
> standVFFB.t(1,1);
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 4
ACTIONS
	VFFB uTorso(2000., 250.).by(rAnkle).over(cop);
	VFFB uTorso(2000., 250.).by(lAnkle).over(cop);
ENDACTIONS
TRANSITION to(-1).after(time 500);
ENDPHASE

ENDSCRIPT
