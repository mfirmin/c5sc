SCRIPTS hak.t, squatVFFB.t;

BEGINSCRIPT HAK_TO_SQUAT(void)

PHASE 0
ACTIONS

	POSE rKnee(2.4), lKnee(2.4);
	POSE rHip(-2.4), lHip(-2.4);
	POSE rAnkle(-.9), lAnkle(-.9);

	VF (0, -2500, 0).on(rHand).by(rShoulder);
	VF (0, -2500, 0).on(lHand).by(lShoulder);


ENDACTIONS
TRANSITION to(1).after(time .2);
ENDPHASE

PHASE 1
> squatVFFB.t(2);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
