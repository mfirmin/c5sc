SCRIPTS standVFFB.t, squatVFFB.t;


BEGINSCRIPT fwdhop(void)

PHASE 0 
> standVFFB.t(1, 1);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
	POSE rElbow(-1.7), lElbow(-1.7);
ENDACTIONS
TRANSITION to(2).after(time 1);
ENDPHASE

PHASE 2 # Start leaning forward
ACTIONS
	POSE rElbow(-.4, 80., 30.), lElbow(-.4, 80., 30.);
	POSE rShoulder(.5, 80., 30.), lShoulder(.5, 80., 30.);
	POSE rHip(-.6, 80., 30.), lHip(-.6, 80., 30.);
	POSE rKnee(.3,120.,30.), lKnee(.3,120.,30.);
	POSE rAnkle(-.4, 80., 30.), lAnkle(-.4, 80., 30.);
ENDACTIONS
TRANSITION to(3).after(time .5);
ENDPHASE

PHASE 3 # Bend knees
ACTIONS
	POSE rHip(-1.3,180., 30.), lHip(-1.3,180.,30.);
	POSE rKnee(1.2, 150., 30.), lKnee(1.2,150.,30.);
	POSE rAnkle(-.5, 100., 10.), lAnkle(-.5, 100., 10.);
ENDACTIONS
TRANSITION to(4).after(time .3);
ENDPHASE

PHASE 4 # Jump!
ACTIONS
	POSE rShoulder(-.5, 80., 30.), lShoulder(-.5,80.,30.);

	VPD uTorso(.75,300,30.).joint(lHip);
	VPD uTorso(.75,300,30.).joint(rHip);

	VF (-200, -3000, 0).on(rFoot).by(rHip);
	VF (-200, -3000, 0).on(lFoot).by(lHip);

    POSE rAnkle(0);
    POSE lAnkle(0);

ENDACTIONS
TRANSITION to(5).after(nocontact rFoot);
ENDPHASE

PHASE 5 # mid jump
ACTIONS
	POSE rHip(-0.7,1000.,100.), lHip(-0.7,1000.,100.);
	POSE rKnee(1.1,1000.,100.), lKnee(1.1,1000.,100.);
	POSE rAnkle(-.4), lAnkle(-.4);
	POSE rShoulder(-1.7,80.,30.), lShoulder(-1.7,80.,30.);
ENDACTIONS
TRANSITION to(7).after(contact rFoot);
ENDPHASE

PHASE 6 # landing
ACTIONS
	POSE rHip(-1.1,1000.,100.), lHip(-1.1,1000.,100.);
	POSE rKnee(1.1,1000.,100.), lKnee(1.1,1000.,100.);
	POSE rAnkle(-.3, 1000., 100.), lAnkle(-.3, 1000., 100.);
ENDACTIONS
TRANSITION to(7).after(time .2);
ENDPHASE

PHASE 7
> standVFFB.t(1, 1);
TRANSITION to(-1).after(fallen x .6);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
