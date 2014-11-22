SCRIPTS balancehighsquat.t, squatVFFB.t, rise.t, balance2ankle.t;


BEGINSCRIPT somersault(void)
PHASE 0 # start to squat
TRANSITION to(1).after(time 2); # Format (transition <next phase> <t=time|c=contact> <seconds|body
ACTIONS # begin listing the actions for this phase
	POSE neck2head(0.0), waist(0.0), lTorso2uTorso(0.0), uTorso2neck(0.0);

	LIPOSE rAnkle(-.7).time(2);
    LIPOSE lAnkle(-.7).time(2);
    LIPOSE rKnee(1.8).time(2);
    LIPOSE lKnee(1.8).time(2);
    LIPOSE rHip(-1.6).time(2);
    LIPOSE lHip(-1.6).time(2);
       

	POSE rShoulder(.1,50.,30.), lShoulder(.1,50.,30.), rElbow(-.8,50.,30.), lElbow(-.8,50.,30.), rWrist(-.5,5.,3.), lWrist(-.5,5.,3.);
ENDACTIONS #stop listing actions
ENDPHASE

PHASE 1 # start leaning forward
TRANSITION to(2).after(time .5); #transition to phase 2 after .5 seconds
ACTIONS
	POSE neck2head(.8);
    POSE rShoulder(-1.7);
    POSE lShoulder(-1.7);
    LIPOSE rAnkle(-.4).time(.5);
    LIPOSE lAnkle(-.4).time(.5);
    LIPOSE lKnee(1.5).time(.5);
    LIPOSE rKnee(1.5).time(.5);
    POSE rHip(-1.9), lHip(-1.9);
    POSE rElbow(-1.0,1000.,100.), lElbow(-1.0,1000.,100.);
    POSE rWrist(-1.2,300.,30.), lWrist(-1.2,300.,30.);
	POSE waist(.8), lTorso2uTorso(.8); 
ENDACTIONS
ENDPHASE

PHASE 2 # spring forward
TRANSITION to(3).after(time .4);
ACTIONS
	POSE rShoulder(-2.1), lShoulder(-2.1);
    POSE rAnkle(.4,500.,20.), lAnkle(.4,500.,20.);
    POSE rKnee(0.0,0.0,0.0), lKnee(0.0,0.0,0.0);
    POSE rHip(0.0,0.0,0.0), lHip(0.0,0.0,0.0);
    POSE rElbow(-1.4,1000.,100.), lElbow(-1.4,1000.,100.);
	VF (-70,-200,0.).on(rFoot).by(rHip);
	VF (-70,-200,0.).on(lFoot).by(lHip);
ENDACTIONS
ENDPHASE

PHASE 3 # start roll
TRANSITION to(4).after(time .2);
ACTIONS
	POSE rAnkle(-.5,100.,30.), lAnkle(-.5,100.,30.), rKnee(2.5,200.,20.), lKnee(2.5,200.,20.), rElbow(-2.2,50.,30.), lElbow(-2.2,50.,30.), rWrist(-1.9,150.,30.), lWrist(-1.9,150.,30.), rHip(-2.5,200.,30.), lHip(-2.5,200.,30.);
ENDACTIONS
ENDPHASE

PHASE 4 # roll and start correcting
TRANSITION to(5).after(contact rFoot);
ACTIONS
	LIPOSE rShoulder(.8,1000.,100.).time(1);
    LIPOSE lShoulder(.8,1000.,100.).time(1);
    POSE rAnkle(0.,100.,30.), lAnkle(0.,100.,30.);
    POSE rKnee(2.9,1000.,100.), lKnee(2.9,1000.,100.);
    POSE rElbow(-.0,100.,30.), lElbow(-.0,100.,30.); 
    POSE rWrist(-.0,300.,30.), lWrist(-.0,300.,30.);
    POSE rHip(-2.5,1000.,100.), lHip(-2.5,1000.,100.);
    POSE waist(.8,600.,60.);
ENDACTIONS
ENDPHASE

PHASE 5
TRANSITION to(6).after(time 1.5);
ACTIONS
	POSE rShoulder(.9,1000.,100.), lShoulder(.9,1000.,100.);
    POSE rAnkle(-.4,100.,30.), lAnkle(-.4,100.,30.);
    POSE rKnee(2.9,1000.,100.), lKnee(2.9,1000.,100.);
    LIPOSE rElbow(-.3,600.,30.).time(1);
    LIPOSE lElbow(-.3,600.,30.).time(1);
	POSE neck2head(0.0);
	LIPOSE rWrist(-.2,300.,30.).time(.7);
    LIPOSE lWrist(-.2,300.,30.).time(.7);
	POSE waist(0.0);
ENDACTIONS
ENDPHASE

PHASE 6
> squatVFFB.t(1);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT

