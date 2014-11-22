
BEGINSCRIPT crawl_base(dt)

PHASE 0
ACTIONS
	POSE neck2head(0.0,1000.,100.), waist(0.0, 1000., 100.), uTorso2neck(0.0,1000.,100.), lTorso2uTorso(0.0, 1000., 100.);

	POSE rHip(-2.2, 1000., 100.), lHip(-1.57, 1000., 100. );
	POSE rKnee(2.8,1000.,100.), lKnee(1.8,1000.,100.);
	POSE rAnkle(-.7,1000.,100.), lAnkle(-.7,1000.,100.);

	POSE rShoulder(-1.4,1000.,100.), lShoulder(-1.4,1000.,100.);
	POSE rElbow(-.7,1000.,100.), lElbow(-1.57,1000.,100.);
	POSE rWrist(-.6,100.,10.), lWrist(-.9,100.,10.);
ENDACTIONS
TRANSITION to(1).after(time dt);
ENDPHASE

PHASE 1
ACTIONS

	POSE rHip(-2.2, 1000., 100.), lHip(-1.57, 1000., 100. );
	POSE rKnee(1.7,1000.,100.), lKnee(1.6,1000.,100.);
	POSE rAnkle(-.7,1000.,100.), lAnkle(-.7,1000.,100.);

	POSE rShoulder(-1.2,1000.,100.), lShoulder(-1.4,1000.,100.);
	POSE rElbow(-1.0,1000.,100.), lElbow(-1,1000.,100.);
	POSE rWrist(-.9,100.,10.), lWrist(-.6,100.,10.);

ENDACTIONS
TRANSITION to(2).after(contact lHand);
ENDPHASE

PHASE 2
ACTIONS
	POSE rHip(-1.57, 1000., 100.), lHip(-2.2, 1000., 100. );
	POSE rKnee(1.8,1000.,100.), lKnee(2.8,1000.,100.);
	POSE rAnkle(-.7,1000.,100.), lAnkle(-.7,1000.,100.);

	POSE rShoulder(-1.5,1000.,100.), lShoulder(-1.4,1000.,100.);
	POSE rElbow(-1.57,1000.,100.), lElbow(-.7,1000.,100.);
	POSE rWrist(-.9,100.,10.), lWrist(-.6,100.,10.);
ENDACTIONS
TRANSITION to(3).after(time dt);
ENDPHASE

PHASE 3
ACTIONS
	POSE lHip(-2.2, 1000., 100.), rHip(-1.57, 1000., 100. );
	POSE lKnee(1.7,1000.,100.), rKnee(1.6,1000.,100.);
	POSE lAnkle(-.7,1000.,100.), rAnkle(-.7,1000.,100.);

	POSE lShoulder(-1.2,1000.,100.), rShoulder(-1.4,1000.,100.);
	POSE lElbow(-1.0,1000.,100.), rElbow(-1,1000.,100.);
	POSE lWrist(-.9,100.,10.), rWrist(-.6,100.,10.);
ENDACTIONS
TRANSITION to(0).after(contact rHand);
ENDPHASE
ENDSCRIPT
