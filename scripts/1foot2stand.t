BEGINSCRIPT STANDINGPOSE(dt)

PHASE 0
ACTIONS
	POSE neck2head(0.,1000.,100.), uTorso2neck(0.,1000.,100.), waist(0.,600.,10.), lTorso2uTorso(0.,600.,10.);

        POSE rElbow(0.0,1000.,100.), lElbow(0.0,1000.,100.);
        POSE rWrist(0.0,100.,10.), lWrist(0.0,100.,10.);

	LIPOSE rShoulder(0.).time(dt);
	LIPOSE lShoulder(0.).time(dt);
	LIPOSE rHip(0.0).time(2);
	LIPOSE lHip(.0).time(2);

        LIPOSE rKnee(0.).time(1); 
	LIPOSE lKnee(0.).time(1);
        LIPOSE rAnkle(0.).time(1);
        LIPOSE lAnkle(0.).time(1);

	VFFB uTorso(2000., 250.).by(rAnkle);
	VFFB uTorso(2000., 250.).by(lAnkle);
ENDACTIONS
TRANSITION to(1).after(time dt);
ENDPHASE

PHASE 1
ACTIONS
	VFFB uTorso(2000., 250.).by(rAnkle);
	VFFB uTorso(2000., 250.).by(lAnkle);
ENDACTIONS
TRANSITION to(-1).after(stable);
ENDPHASE

ENDSCRIPT
