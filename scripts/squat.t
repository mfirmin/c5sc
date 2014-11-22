BEGINSCRIPT SQUATPOSE(void)
PHASE 0 # start to squat
TRANSITION to(1).after(time 3);
ACTIONS
	POSE lTorso2uTorso(0., 600., 60.), uTorso2neck(0.), neck2head(0.);
	POSE waist(0.1,600.,60.);
	POSE rAnkle(-.5,400.,160.), lAnkle(-.5,400.,160.), lKnee(1.9,300.,300.), rKnee(1.9,300.,300.), rHip(-1.4,600.,200.), lHip(-1.4,600.,200.), rShoulder(-1.7,50.,30.), lShoulder(-1.7,50.,30.), rElbow(-0.,50.,30.), lElbow(-0.,50.,30.), rWrist(-.2,5.,3.), lWrist(-.2,5.,3.);
	POSEFB rAnkle(2.2,2.).on(joint lAnkle), lAnkle(2.2,2.).on(joint lAnkle);
ENDACTIONS
ENDPHASE

PHASE 1 
TRANSITION to(-1).after(time 1);
ACTIONS
	POSE rAnkle(-.5,400.,160.), lAnkle(-.5,400.,160.);
ENDACTIONS
ENDPHASE
ENDSCRIPT
