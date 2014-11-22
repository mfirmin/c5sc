BEGINSCRIPT rise(void)
PHASE 0 # stand up
TRANSITION to(1).after(time .5);
ACTIONS
	POSE rWrist(0.0), lWrist(0.0), rElbow(0.0), lElbow(0.0), neck2head(0.0), waist(0.0), uTorso2neck(0.0), lTorso2uTorso(0.0);
	POSE rAnkle(-.2,120.,90.), lAnkle(-.2,120.,90.), rKnee(0.,110.,80.), lKnee(0.,110.,80.), rHip(-.4,200.,90.), lHip(-.4,200.,90.), rShoulder(-.7,300.,30.), lShoulder(-.7,300.,30.);
	POSEFB rAnkle(5.2,.5).on(part lFoot), lAnkle(5.2,.5).on(part lFoot), rHip(2.2,.5).on(part lFoot), lHip(2.2,.5).on(part lFoot);
ENDACTIONS
ENDPHASE

PHASE 1 # correct
TRANSITION to(-1).after(time 1);
ACTIONS
	POSE rAnkle(0.,200.,80.), lAnkle(0.,200.,80.), rKnee(0.,200.,80.), lKnee(0.,200.,80.), rHip(0.,230.,70.), lHip(0.,230.,70.), rShoulder(0.,0.,30.), lShoulder(0.,0.,30.);
	POSEFB rAnkle(5.2,.5).on(part lFoot), lAnkle(5.2,.5).on(part lFoot);
ENDACTIONS
ENDPHASE

ENDSCRIPT
