SCRIPTS step.t, balancecop.t, walk.s, runOPT.s;

BEGINSCRIPT fwdhandspring(void)
PHASE 0 # start with a walk step
> step.t(void);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1 # start leaning forward
TRANSITION to(2).after(time .5);
ACTIONS
	POSE rShoulder(-1.7,150.,30.), lShoulder(-1.7,150.,30.);
	POSE lKnee(0.05), rKnee(.5); 
	POSE lHip(.3,200.,30.), rHip(-1,200.,30.);
	POSE rAnkle(0.), lAnkle(.4); 
	POSE rElbow(-.5), lElbow(-.5);
ENDACTIONS
ENDPHASE

PHASE 2 # lean forward
TRANSITION to(3).after(time .2);
ACTIONS
	POSE waist(.3), lTorso2uTorso(.3);
	POSE rShoulder(-1.8), lShoulder(-1.8);
	POSE rWrist(-1.5), lWrist(-1.5);
	POSE lKnee(0.05,500,30), rKnee(.3); 
	POSE rHip(-1.2,200.,30.), lHip(.3,200.,30.); 
	POSE rAnkle(.2), lAnkle(.4);
	POSE rElbow(-.2), lElbow(-.2);
ENDACTIONS
ENDPHASE

PHASE 3 # contact hands to ground
TRANSITION to(4).after(contact lHand);
ACTIONS
	POSE rShoulder(-2.3), lShoulder(-2.3); 
	POSE rWrist(-1), lWrist(-1); 
	POSE rHip(-1.5), lHip(.3);
	POSE rAnkle(.8);
ENDACTIONS
ENDPHASE


PHASE 4 # kick up
TRANSITION to(5).after(time .3);
ACTIONS
	POSE rShoulder(-2.5,500.,30.), lShoulder(-2.5,500.,30.), rElbow(-.5), lElbow(-.5), rWrist(-1.5), lWrist(-1.5), rHip(-1.6), lHip(1.6,300.,200.), rKnee(0.), lKnee(0.), rAnkle(.4), lAnkle(0.);
	#POSE waist(-.3, 600., 60.), lTorso2uTorso(-.3, 600., 60.);
ENDACTIONS
ENDPHASE

PHASE 5 # balance
TRANSITION to(6).after(time .4);
ACTIONS
	POSE waist(-.2,300,100), lTorso2uTorso(-.2,300,100);
	POSE rShoulder(-2.5,300.,30.), lShoulder(-2.5,300.,30.), rElbow(-.8), lElbow(-.8), rWrist(-1.7), lWrist(-1.7), rAnkle(.2), lAnkle(.2), rKnee(.5), lKnee(.5);
	POSE rHip(-1.4), lHip(2.3,300.,200.);
ENDACTIONS
ENDPHASE

PHASE 6 # prepare for landing
TRANSITION to(7).after(contact lFoot);
ACTIONS
	POSE rHip(-.3), lHip(2.,1000.,100.);
	POSE rKnee(.4), lKnee(1.4), waist(-.4), lTorso2uTorso(-.4), rShoulder(-2.7), lShoulder(-2.7);
	POSE rAnkle(.4), lAnkle(-.8);
ENDACTIONS
ENDPHASE

PHASE 7 # land
TRANSITION to(8).after(time 1);
ACTIONS
	POSE waist(-.1,600.,60.), lTorso2uTorso(0.,600.,60.);
	POSE rKnee(1.3), lKnee(.3), rHip(-.1), lHip(.2);
	POSE rAnkle(-.0), lAnkle(-.7);
	POSE rShoulder(0.,100.,30.), lShoulder(0.,100.,30.), rElbow(0.), lElbow(0.), rWrist(0.), lWrist(0.);
ENDACTIONS
ENDPHASE

PHASE 8
> runOPT.s(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
