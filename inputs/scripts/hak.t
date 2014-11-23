
BEGINSCRIPT HAKPOSE(dt)

PHASE 0
ACTIONS
	POSE lTorso2uTorso(0., 600., 60.), uTorso2neck(0.), neck2head(0.);
	POSE waist(0.0,600.,60.);

	LIPOSE lKnee(1.6,1000.,100.).time(dt);
    LIPOSE rKnee(1.6,1000.,100.).time(dt);
	LIPOSE rAnkle(-1.5,1000.,100.).time(dt); 
    LIPOSE lAnkle(-1.5,1000.,100.).time(dt);

	LIPOSE rElbow(-1.,1000.,100.).time(dt);
    LIPOSE lElbow(-1.,1000.,100.).time(dt);
	LIPOSE rShoulder(-0.5,1000.,100.).time(dt);
    LIPOSE lShoulder(-0.5,1000.,100.).time(dt);
	POSE rWrist(-.8,5.,3.), lWrist(-.8,5.,3.);
	LIPOSE rHip(-2.8, 1000., 100.).time(dt);
    MATCH lHip.to(rHip);
ENDACTIONS
TRANSITION to(-1).after(time dt);
ENDPHASE

ENDSCRIPT
