BEGINSCRIPT STANDINGPOSE(dt)

PHASE 0
TRANSITION to(-1).after(time dt);
ACTIONS
	POSE neck2head(0.,600.,60.), uTorso2neck(0.,600.,60.), waist(0.,600.,60.), lTorso2uTorso(0.,600.,60.);
        POSE rElbow(0.0), lElbow(0.0);
        POSE rWrist(0.0,5.,3.), lWrist(0.0,5.,3.);
        POSE rKnee(0.0,300.,200.), lKnee(0.,300.,200.);
        POSE rHip(0.,300.,60.), lHip(0.,300.,60.);
        POSE rShoulder(0.,150.,80.), lShoulder(0.,150.,80.);
        POSE rAnkle(-.005,500.,100.), lAnkle(-0.005,500.,100.);
ENDACTIONS
ENDPHASE
ENDSCRIPT
