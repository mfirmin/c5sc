SCRIPTS step.t, balancecop.t;


BEGINSCRIPT handstand(dt)
PHASE 0 # start with a walk step
> step.t(void);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1 # start leaning forward
TRANSITION to(2).after(time .5);
ACTIONS
	POSE rShoulder(-1.7,150.,30.), lShoulder(-1.7,150.,30.), lKnee(0.05), rKnee(.5), lHip(.3,200.,30.), rHip(-1,200.,30.), rAnkle(0.), lAnkle(.4), rElbow(-.5), lElbow(-.5);
ENDACTIONS
ENDPHASE

PHASE 2 # lean forward
TRANSITION to(3).after(time .2);
ACTIONS
	POSE waist(.3), lTorso2uTorso(.3);
	POSE rShoulder(-1.6), lShoulder(-1.6), rWrist(-1.5), lWrist(-1.5), lKnee(0.05,500,30), rKnee(.3), rHip(-1.2,200.,30.), lHip(.3,200.,30.), rAnkle(.2), lAnkle(.4);
    POSE rElbow(-.28), lElbow(-.28);
ENDACTIONS
ENDPHASE

PHASE 3 # contact hands to ground
ACTIONS
	POSE rShoulder(-2.75), lShoulder(-2.75);
    POSE rWrist(-1.3), lWrist(-1.3), rHip(-1.2), lHip(.3), rAnkle(.8);
	POSE rElbow(-.6), lElbow(-.6);
ENDACTIONS
TRANSITION to(4).after(contact lHand);
ENDPHASE


PHASE 4 # kick up
ACTIONS
	POSE rShoulder(-2.85,1000.,100.), lShoulder(-2.85,1000.,100.);
        POSE rElbow(-.7,1000.,100.), lElbow(-.7,1000.,100.);
        POSE rWrist(-1.25, 300., 30.), lWrist(-1.25, 300., 30.);
        POSE rHip(-.9), lHip(-.7,400.,200.);
        POSE rKnee(.7,1000.,100.), lKnee(.7,1000.,100.);
        POSE rAnkle(.0), lAnkle(0.);
ENDACTIONS
TRANSITION to(5).after(time .3);
ENDPHASE

PHASE 5 # balance
ACTIONS
	POSE waist(0.0,2000,100.), lTorso2uTorso(-.0,1000.,100.);
	POSE rHip(-.7,1000.,100.), lHip(-.7,1000.,100.);
        POSE rKnee(1.,1000.,100.), lKnee(1.,1000.,100.);
        POSE rWrist(-1.2, 300., 30.), lWrist(-1.2, 300., 30.);

    POSEFB rHip(-2.0,.0).on(part rHand);
    POSEFB lHip(-2.0,.0).on(part rHand);
    POSEFB rWrist(2.0,1.0).on(part rHand);
    POSEFB lWrist(2.0,1.0).on(part rHand);

        
ENDACTIONS
TRANSITION to(-1).after(anglerange -2 2.8);
TRANSITION to(-1).after(time dt);
ENDPHASE

ENDSCRIPT
