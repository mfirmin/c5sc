BEGINSCRIPT step(void)
PHASE 0
TRANSITION to(1).after(time .4);
ACTIONS
	POSE neck2head(0.0), lTorso2uTorso(0.0, 600., 30.), uTorso2neck(0.0), waist(0.0, 600., 30.), rWrist(0.0), lWrist(0.0), rKnee(0.9), rAnkle(-0.2), lKnee(0.05), lAnkle(-0.2), rShoulder(.1,100.,30.), rElbow(0,100.,30.), lShoulder(-.1,100.,30.), lElbow(-.3, 100., 30.), rHip(-.7), lHip(0.0);
ENDACTIONS
ENDPHASE

PHASE 1
TRANSITION to(-1).after(contact rFoot);
ACTIONS
	POSE rKnee(.4), rAnkle(-.2), lKnee(0.05), lAnkle(0.0), rShoulder(.1,100.,30.), rElbow(0,100.,30.), lShoulder(-.1,100.,30.), lElbow(-.3,100.,30.), rHip(-.7), lHip(.4,200.,90.);
ENDACTIONS
ENDPHASE
ENDSCRIPT
