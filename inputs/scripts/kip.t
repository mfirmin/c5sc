SCRIPTS squatVFFB.t;

BEGINSCRIPT kip(void)

PHASE 0 #Retract
ACTIONS
	POSE neck2head(0.,1000.,100.), uTorso2neck(0.,1000.,100.), lTorso2uTorso(0.,1000.,100.), waist(0.,1000.,100.);
	LIPOSE rAnkle(0.).time(.6);
    LIPOSE lAnkle(0.).time(.6);
	LIPOSE rKnee(2.8).time(.6); 
    LIPOSE lKnee(2.8).time(.6);

	LIPOSE rHip(-1.4).time(.6);
    LIPOSE lHip(-1.4).time(.6);

	LIPOSE rShoulder(-2.6).time(.6);
    LIPOSE lShoulder(-2.6).time(.6);
	LIPOSE rElbow(-2.27).time(.6);
    LIPOSE lElbow(-2.27).time(.6);
	POSE rWrist(-1.57);
    POSE lWrist(-1.57);
ENDACTIONS
TRANSITION to(1).after(time 1);
ENDPHASE

PHASE 1 #Retract more, throw feet
ACTIONS
	POSE lKnee(0.), rKnee(0.);
	POSE lHip(-1.7), rHip(-1.7);
	VF (0., 0500., 0).on(rFoot).by(rHip);
	VF (0., 0500., 0).on(lFoot).by(lHip);
ENDACTIONS
TRANSITION to(2).after(time .3);
ENDPHASE

PHASE 2 #Throw Lower Body
ACTIONS
	POSE rAnkle(-1.0), lAnkle(-1.0);
	POSE rKnee(1.505,1000.,100.), lKnee(1.505,1000.,100.);
	POSE rHip(.78), lHip(.78);
	VF (0., -4000., 0.).on(rHand).by(rShoulder);
	VF (0., -4000., 0.).on(lHand).by(lShoulder);
ENDACTIONS
TRANSITION to(3).after(contact rFoot);
ENDPHASE

PHASE 3 #Throw Upper Body
ACTIONS
	POSE waist(0.4,600.,60.);
	POSE rAnkle(-.4,1000.,100.), lAnkle(-.4,1000.,100.);
	POSE rShoulder(-1.7), lShoulder(-1.7);
        POSE rElbow(-0.,50.,30.), lElbow(-0.,50.,30.);
        POSE rWrist(-.2,5.,3.), lWrist(-.2,5.,3.);
	LIPOSE rHip(-1.1, 1000., 100.).time(.5);
    LIPOSE lHip(-1.1, 1000., 100.).time(.5);
	VFFB uTorso(1800., 100.).by(rAnkle).over(cop);
	VFFB uTorso(1800., 100.).by(lAnkle).over(cop);
ENDACTIONS
TRANSITION to(4).after(time 1);
ENDPHASE

PHASE 4
> squatVFFB.t(2);
TRANSITION to(0).after(fallen < -.6);
TRANSITION to(-1).after(fallen > 1.2);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
