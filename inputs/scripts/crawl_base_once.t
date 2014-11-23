

BEGINSCRIPT crawl(dt)

PHASE 0
ACTIONS
	POSE neck2head(-1.0,1000.,100.), waist(-2.0, 1000., 100.), uTorso2neck(0.0,1000.,100.), lTorso2uTorso(0.0, 1000., 100.);

	POSE rHip(-2.3, 1000., 100.), lHip(-1.7, 1000., 100. );
	POSE rKnee(1.95,1000.,100.), lKnee(1.5,1000.,100.);
	POSE rAnkle(0.0,1000.,100.), lAnkle(-.2,1000.,100.);

	POSE rShoulder(-1.1,1000.,100.), lShoulder(-0.7,1000.,100.);
	POSE rElbow(-0.8,1000.,100.), lElbow(-1.7, 1000.,100.);
	POSE rWrist(-0.8,100.,10.), lWrist(-0.50,100.,10.);
ENDACTIONS
TRANSITION to(1).after(time dt);
ENDPHASE

PHASE 1
ACTIONS
	POSE rHip(-2.3, 1000., 100.), lHip(-1.4, 1000., 100. );
	POSE rKnee(2.0,1000.,100.), lKnee(1.1,1000.,100.);
	POSE rAnkle(-.7,1000.,100.), lAnkle(-.5,1000.,100.);

	POSE rShoulder(-0.7,1000.,100.), lShoulder(-1.6,1000.,100.);
	POSE rElbow(-0.9,1000.,100.), lElbow(-0.6, 1000.,100.);
	POSE rWrist(-.9,100.,10.), lWrist(-.6,100.,10.);
ENDACTIONS
TRANSITION to(2).after(contact lHand);
ENDPHASE

PHASE 2
ACTIONS
	POSE rHip(-1.9, 1000., 100.), lHip(-2.3, 1000., 100. );
	POSE rKnee(1.6,1000.,100.), lKnee(2.2,1000.,100.);
	POSE rAnkle(-.7,1000.,100.), lAnkle(0.0,1000.,100.);

	POSE rShoulder(-0.7,1000.,100.), lShoulder(-1.05,1000.,100.);
	POSE rElbow(-1.6,1000.,100.), lElbow(-0.5, 1000.,100.);
	POSE rWrist(-0.3,100.,10.), lWrist(-1.2,100.,10.);
ENDACTIONS
TRANSITION to(3).after(time dt);
ENDPHASE

PHASE 3
ACTIONS
	POSE rHip(-1.5, 1000., 100.), lHip(-2.1, 1000., 100. );
	POSE rKnee(1.1,1000.,100.), lKnee(1.7,1000.,100.);
	POSE rAnkle(-.7,1000.,100.), lAnkle(-.2,1000.,100.);

	POSE rShoulder(-1.5,1000.,100.), lShoulder(-0.7,1000.,100.);
	POSE rElbow(-0.7,1000.,100.), lElbow(-0.9, 1000.,100.);
	POSE rWrist(-0.8,100.,10.), lWrist(-1.1,100.,10.);
ENDACTIONS
TRANSITION to(-1).after(contact rHand);
ENDPHASE



ENDSCRIPT
