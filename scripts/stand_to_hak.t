BEGINSCRIPT STAND_TO_HAK(void)
PHASE 0 # start to squat
ACTIONS
	POSE lTorso2uTorso(0., 600., 60.), uTorso2neck(0.), neck2head(0.);
	POSE waist(0.1,600.,60.);
	LIPOSE rAnkle(-1.4).time(1);
    LIPOSE lAnkle(-1.4).time(1);
    LIPOSE lKnee(1.6).time(1);
    LIPOSE rKnee(1.6).time(1);
    LIPOSE rHip(-1.4).time(1);
    LIPOSE lHip(-1.4).time(1);
    POSE rShoulder(-1.7,50.,30.), lShoulder(-1.7,50.,30.);
    POSE rElbow(-0.,50.,30.), lElbow(-0.,50.,30.);
    POSE rWrist(-.2,5.,3.), lWrist(-.2,5.,3.);
	POSEFB rAnkle(2.2,2.).on(joint lAnkle), lAnkle(2.2,2.).on(joint lAnkle);
ENDACTIONS
TRANSITION to(2).after(time 1);
ENDPHASE

PHASE 1 
TRANSITION to(2).after(time 0.5);
ACTIONS
	POSE rAnkle(-1.4), lAnkle(-1.4);
ENDACTIONS
ENDPHASE

# landing with hands
PHASE 2
TRANSITION to(3).after(time 0.8);
ACTIONS
	POSE rAnkle(-1.4), lAnkle(-1.4);
	POSE lKnee(1.3,300.,30.), rKnee(1.3,300.,30.);
	POSE rShoulder(-1.4,1000.,100.), lShoulder(-1.4,1000.,100.);
	POSE rElbow(-1., 1000., 100.), lElbow(-1.,1000.,100.);
	POSE rWrist(-.8,5.,3.), lWrist(-.8,5.,3.);
ENDACTIONS
ENDPHASE

# 
PHASE 3
TRANSITION to(-1).after(time 0.4);
ACTIONS
	POSE lKnee(1.8,1000.,100.), rKnee(1.8,1000.,100.);
	POSE rAnkle(-1.,1000.,100.), lAnkle(-1.,1000.,100.);
	POSE rElbow(-1.,1000.,100.), lElbow(-1.,1000.,100.);
ENDACTIONS
ENDPHASE

ENDSCRIPT
