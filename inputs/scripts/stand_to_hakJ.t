BEGINSCRIPT STAND_TO_PRONE(void)

PHASE 0
ACTIONS
	POSE neck2head(0.0);
	POSE lTorso2uTorso(0.0, 600., 30.);
	POSE uTorso2neck(0.0), waist(0.0, 600., 30.);
	POSE rKnee(0.9), lKnee(0.05);
	POSE rAnkle(-0.2), lAnkle(-0.2); 
	POSE rShoulder(.1,100.,30.), lShoulder(-.1,100.,30.);
	POSE rElbow(0,100.,30.), lElbow(-.3, 100., 30.);
	POSE rHip(-.7), lHip(0.0);
ENDACTIONS
	TRANSITION to(1).after(time .4);
ENDPHASE

PHASE 1
ACTIONS
	POSE rKnee(.4), lKnee(0.05);
	POSE rAnkle(0.1), lAnkle(0.0);
	POSE rShoulder(.1,100.,30.), lShoulder(-.1,100.,30.);
	POSE rElbow(0,100.,30.), lElbow(-.3,100.,30.);
	POSE rHip(-.7), lHip(.4,200.,90.);
ENDACTIONS
	TRANSITION to(2).after(contact rFoot);
ENDPHASE

PHASE 2
ACTIONS
	POSE waist(0.0, 600., 0.3);

	LIPOSE rShoulder(-0.40).time(1);
	LIPOSE lShoulder(-0.30).time(1);
	LIPOSE rElbow(-1.2).time(1);
	LIPOSE lElbow(-1.0).time(1);

	LIPOSE rHip(-2).time(1);
    	LIPOSE lHip(-0.2).time(1);
    	LIPOSE lKnee(1.6).time(1);
    	LIPOSE rKnee(1.8).time(1);
	LIPOSE lAnkle(-0.2).time(1);
    	LIPOSE rAnkle(-0.2).time(1);
ENDACTIONS
	TRANSITION to(3).after(time 1);
ENDPHASE

PHASE 3
ACTIONS
	LIPOSE waist(1).time(0.5);

	LIPOSE rShoulder(-1.5).time(0.5);
	LIPOSE lShoulder(-1.5).time(0.5);
	LIPOSE rElbow(-0.8).time(0.5);
	LIPOSE lElbow(-0.8).time(0.5);

	POSE rWrist(-1.0, 6, 0.60);
	POSE lWrist(-1.0, 6, 0.60);

	LIPOSE rHip(-2.5).time(0.5);
    	LIPOSE lHip(-1).time(0.5);
    	LIPOSE lKnee(1.1).time(0.5);
    	LIPOSE rKnee(2.0).time(0.5);
	LIPOSE lAnkle(-0.2).time(0.5);
    	LIPOSE rAnkle(-0.85).time(0.5);
ENDACTIONS
	TRANSITION to(4).after(contact rHand);
ENDPHASE

PHASE 4
ACTIONS
	LIPOSE waist(1).time(1);

	LIPOSE rShoulder(-1.5).time(0.5);
	LIPOSE lShoulder(-1.5).time(0.5);
	LIPOSE rElbow(-0.9).time(1);
	LIPOSE lElbow(-0.9).time(1);

	POSE rWrist(-1.0, 0.6, 0.60);
	POSE lWrist(-1.0, 0.6, 0.60);

	LIPOSE rHip(-2.3).time(0.25);
    	LIPOSE lHip(-1.1).time(0.25);
    	LIPOSE lKnee(1.1).time(0.2);
    	LIPOSE rKnee(2.4).time(0.15);
	LIPOSE lAnkle(-0.2).time(1);
    	LIPOSE rAnkle(-0.65).time(0.25);
ENDACTIONS
	TRANSITION to(5).after(time 0.3);
ENDPHASE

PHASE 5
ACTIONS
	LIPOSE waist(1).time(1);

	LIPOSE rShoulder(-1.5).time(0.5);
	LIPOSE lShoulder(-1.5).time(0.5);
	LIPOSE rElbow(-0.8).time(1);
	LIPOSE lElbow(-0.8).time(1);

	POSE rWrist(-1.0, 0.6, 0.60);
	POSE lWrist(-1.0, 0.6, 0.60);

	LIPOSE rHip(-1.7).time(0.25);
    	LIPOSE lHip(-1).time(0.25);
    	LIPOSE lKnee(1.2).time(0.2);
    	LIPOSE rKnee(1.9).time(1.0);
	LIPOSE lAnkle(-0.2).time(1);
    	LIPOSE rAnkle(-0.65).time(0.25);
ENDACTIONS
	TRANSITION to(6).after(time 0.25);
ENDPHASE

PHASE 6
ACTIONS
	LIPOSE waist(1).time(1);

	LIPOSE rShoulder(-1.5).time(0.5);
	LIPOSE lShoulder(-1.5).time(0.5);
	LIPOSE rElbow(-0.8).time(1);
	LIPOSE lElbow(-0.8).time(1);

	POSE rWrist(-1.0, 0.6, 0.60);
	POSE lWrist(-1.0, 0.6, 0.60);

	LIPOSE rHip(-1.3).time(0.15);
    	LIPOSE lHip(-1).time(0.15);
    	LIPOSE lKnee(1.7).time(0.15);
    	LIPOSE rKnee(1.85).time(0.15);
	LIPOSE lAnkle(-0.2).time(1);
    	LIPOSE rAnkle(-0.5).time(0.25);
ENDACTIONS
	TRANSITION to(-1).after(contact rFoot);
ENDPHASE

ENDSCRIPT
