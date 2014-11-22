SCRIPTS walk.s;

BEGINSCRIPT fwdfrommid(void)

PHASE 0
LOAD fwdhsmid.sav;
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1 # balance
TRANSITION to(2).after(time .4);
ACTIONS
	POSE waist(-.2,300,100), lTorso2uTorso(-.2,300,100);
	POSE rShoulder(-2.5,300.,30.), lShoulder(-2.5,300.,30.), rElbow(-.8), lElbow(-.8), rWrist(-1.7), lWrist(-1.7), rAnkle(.2), lAnkle(.2), rKnee(.5), lKnee(.5);
	POSE rHip(-1.4), lHip(2.3,300.,200.);
ENDACTIONS
ENDPHASE

PHASE 2 # prepare for landing
TRANSITION to(3).after(contact lFoot);
ACTIONS
	POSE rHip(-.3), lHip(2.,1000.,100.);
	POSE rKnee(.4), lKnee(1.4), waist(-.4), lTorso2uTorso(-.4), rShoulder(-2.7), lShoulder(-2.7);
	POSE rAnkle(.4), lAnkle(-.8);
ENDACTIONS
ENDPHASE

PHASE 3 # land
TRANSITION to(4).after(time 1);
ACTIONS
	POSE waist(-.1,600.,60.), lTorso2uTorso(0.,600.,60.);
	POSE rKnee(1.3), lKnee(.3), rHip(-.1), lHip(.2);
	POSE rAnkle(-.0), lAnkle(-.7);
	POSE rShoulder(0.,100.,30.), lShoulder(0.,100.,30.), rElbow(0.), lElbow(0.), rWrist(0.), lWrist(0.);
ENDACTIONS
ENDPHASE

PHASE 4
> walk.s(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
