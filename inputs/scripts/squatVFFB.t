BEGINSCRIPT SQUATPOSE(dt)
PHASE 0
ACTIONS
	LIPOSE neck2head(0.,1000.,100.).time(dt);
    LIPOSE uTorso2neck(0.,1000.,100.).time(dt);
    LIPOSE lTorso2uTorso(0.,600.,10.).time(dt);
    LIPOSE waist(0.0,600.,10.).time(dt);

    POSE rElbow(-0.,50.,30.), lElbow(-0.,50.,30.);
    POSE rWrist(-.2,5.,3.), lWrist(-.2,5.,3.);



	LIPOSE rShoulder(-1.7).time(dt);
	LIPOSE lShoulder(-1.7).time(dt);
	LIPOSE rHip(-1.6).time(dt);
	LIPOSE lHip(-1.6).time(dt);

        LIPOSE rKnee(2.).time(dt); 
	LIPOSE lKnee(2.).time(dt);
        LIPOSE rAnkle(-.6).time(dt);
        LIPOSE lAnkle(-.6).time(dt);

	VFFB uTorso(2000.,250.).by(rAnkle).over(cop);
	VFFB uTorso(2000., 250.).by(lAnkle).over(cop);


ENDACTIONS
TRANSITION to(-1).after(fallen x 1.2);
TRANSITION to(1).after(time dt);
ENDPHASE

# should be stable even without the VFFB
PHASE 1
ACTIONS
	VFFB uTorso(2000., 450.).by(rAnkle).over(cop);
	VFFB uTorso(2000., 450.).by(lAnkle).over(cop);
ENDACTIONS
TRANSITION to(-1).after(fallen x 1.2);
TRANSITION to(-1).after(stable .01);
ENDPHASE
ENDSCRIPT
