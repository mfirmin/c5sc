SCRIPTS standVFFB.t, handstand.t, handstand2supine.t, kip.t, handstandwalk.t, walkonhandsOPT.s;

BEGINSCRIPT walking_handstand(void)

PHASE 0
> standVFFB.t(2, 2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> handstand.t(2);
TRANSITION to(-1).after(anglerange -2 2.8);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> handstandwalk.t(void);
TRANSITION to(-1).after(anglerange -2 2.8);
TRANSITION to(3).after(iterations 3);
ENDPHASE

PHASE 3
> walkonhandsOPT.s(void);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 4 # prepare for landing
TRANSITION to(5).after(contact lFoot);
ACTIONS
	POSE rHip(-.3), lHip(2.,1000.,100.);
	POSE rKnee(.4), lKnee(1.4), waist(-.4), lTorso2uTorso(-.4), rShoulder(-2.7), lShoulder(-2.7);
	POSE rAnkle(.4), lAnkle(-.8);
ENDACTIONS
ENDPHASE

PHASE 5 # land
TRANSITION to(-1).after(time 1);
ACTIONS
	POSE waist(-.1,600.,60.), lTorso2uTorso(0.,600.,60.);
	POSE rKnee(1.3), lKnee(.3), rHip(-.1), lHip(.2);
	POSE rAnkle(-.0), lAnkle(-.7);
	POSE rShoulder(0.,100.,30.), lShoulder(0.,100.,30.), rElbow(0.), lElbow(0.), rWrist(0.), lWrist(0.);
ENDACTIONS
ENDPHASE

ENDSCRIPT
