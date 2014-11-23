BEGINSCRIPT STAND_TO_PRONE(void)
PHASE 0 # start to squat
TRANSITION to(1).after(time 1);
ACTIONS
	POSE lTorso2uTorso(0., 600., 60.), uTorso2neck(0.), neck2head(0.);
	POSE waist(0.1,600.,60.);
	POSE rAnkle(-.5,400.,160.), lAnkle(-.5,400.,160.), lKnee(1.9,300.,300.), rKnee(1.9,300.,300.), rHip(-1.4,600.,200.), lHip(-1.4,600.,200.), rShoulder(-1.7,50.,30.), lShoulder(-1.7,50.,30.), rElbow(-0.,50.,30.), lElbow(-0.,50.,30.), rWrist(-.2,5.,3.), lWrist(-.2,5.,3.);
	POSEFB rAnkle(2.2,2.).on(joint lAnkle), lAnkle(2.2,2.).on(joint lAnkle);
ENDACTIONS
ENDPHASE

PHASE 1 
TRANSITION to(2).after(time 0.5);
ACTIONS
	POSE rAnkle(-.4,400.,160.), lAnkle(-.4,400.,160.);
ENDACTIONS
ENDPHASE

# landing with hands
PHASE 2
TRANSITION to(3).after(time 0.8);
ACTIONS
	POSE lKnee(1.3,300.,300.), rKnee(1.3,300.,300.);
	POSE rAnkle(-.8,400.,160.), lAnkle(-.8,400.,160.);
	POSE rShoulder(-2.,50.,30.), lShoulder(-2.,50.,30.);
	POSE rWrist(-1.8,5.,3.), lWrist(-1.8,5.,3.);
ENDACTIONS
ENDPHASE

# 
PHASE 3
TRANSITION to(4).after(time 0.4);
ACTIONS
	POSE lKnee(1.8,300.,300.), rKnee(1.8,300.,300.);
	POSE rAnkle(-1.4,400.,160.), lAnkle(-1.4,400.,160.);
	POSE rElbow(-1.0,50.,30.), lElbow(-1.0,50.,30.), rWrist(-.2,5.,3.);
ENDACTIONS
ENDPHASE

# curl the knee of the non-supporting leg
PHASE 4
TRANSITION to(5).after(time 0.8);
ACTIONS
	POSE rKnee(2.6,300.,300.);
	SVF(0., 800., 0.).on(uTorso).by(lAnkle);
ENDACTIONS
ENDPHASE

# stretch the non-supporting knee
PHASE 5
TRANSITION to(6).after(time 1.);
ACTIONS
	POSE rHip(-0.,600.,200.);
	POSE rKnee(0.4,300.,300.), lKnee(2.2,300.,300.);
	POSE rAnkle(-1.2,400.,160.), lAnkle(-1.9,400.,160.);
ENDACTIONS
ENDPHASE

PHASE 6
TRANSITION to(7).after(time 1);
ACTIONS
	POSE lKnee(2.8,300.,200.);
ENDACTIONS
ENDPHASE

PHASE 7
TRANSITION to(8).after(time 1);
ACTIONS
	POSE lHip(-0.05,600.,200.);
	POSE lKnee(0.2,300.,300.);
	POSE lAnkle(-1.2,400.,160.);
ENDACTIONS
ENDPHASE

PHASE 8
TRANSITION to(-1).after(time 2);
ACTIONS
	POSE lElbow(-2.1,50.,30.), rElbow(-2.1,50.,30.);
	POSE lShoulder(-0.2,50.,30.), rShoulder(-.2,50.,30.);
ENDACTIONS
ENDPHASE

ENDSCRIPT
