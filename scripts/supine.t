BEGINSCRIPT SUPINE_POSE(void)

PHASE 0
ACTIONS
	POSE neck2head(0.,1000.,100.), uTorso2neck(0.,1000.,100.), lTorso2uTorso(0.,600.,10.), waist(0.,600.,10.);
	POSE rShoulder(0.0,1000.,100.), lShoulder(0.0,1000.,100.);
	POSE rElbow(0.0,1000.,100.), lElbow(0.0,1000.,100.);
	POSE rWrist(0.0,5.,3.), lWrist(0.0,5.,3.);

	POSE rHip(0.0,1000.,100.), lHip(0.0,1000.,100.);
	POSE rKnee(0.0,1000.,100.), lKnee(0.0,1000.,100.);
	POSE rAnkle(0.0,1000.,100.), lAnkle(0.0,1000.,100.);
ENDACTIONS
TRANSITION to(-1).after(stable);
ENDPHASE
ENDSCRIPT
