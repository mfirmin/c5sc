BEGINSCRIPT STANDINGPOSE(dt, dtt)

PHASE 0
ACTIONS
	POSE neck2head(0.,1000.,100.), uTorso2neck(0.,1000.,100.), waist(0.,600.,10.), lTorso2uTorso(0.,600.,60.);

        POSE rElbow(0.0,1000.,100.), lElbow(0.0,1000.,100.);
        POSE rWrist(0.0,100.,10.), lWrist(0.0,100.,10.);

	LIPOSE rShoulder(0.).time(dt);
	LIPOSE lShoulder(0.).time(dt);
	LIPOSE rHip(0.0).time(dt);
	LIPOSE lHip(.0).time(dt);

        LIPOSE rKnee(0.).time(dt); 
	LIPOSE lKnee(0.).time(dt);
        LIPOSE rAnkle(0.).time(dt);
        LIPOSE lAnkle(0.).time(dt);

	VFFB uTorso(2000., 250.).by(rAnkle).over(cop);
	VFFB uTorso(2000., 250.).by(lAnkle).over(cop);
ENDACTIONS
TRANSITION to(1).after(time dtt);
ENDPHASE

PHASE 1
ACTIONS
	VFFB uTorso(2000., 250.).by(rAnkle).over(cop);
	VFFB uTorso(2000., 250.).by(lAnkle).over(cop);
ENDACTIONS
TRANSITION to(-1).after(stable .01);
ENDPHASE

ENDSCRIPT
