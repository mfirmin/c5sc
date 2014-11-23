BEGINSCRIPT highsquatbalance(dt)
PHASE 0 # balance_squat
TRANSITION to(-1).after(time dt);
ACTIONS

	POSE rAnkle(-.5,1000.,100.), lAnkle(-.5,1000.,100.), rKnee(2.,200.,100.), lKnee(2.,200.,100.), rHip(-2.4,1000.,100.), lHip(-2.4,1000.,100.), rShoulder(-2.,1000.,100.), lShoulder(-2.,1000.,100.), rElbow(-1.7,50.,30.), lElbow(-1.7,50.,30.), rWrist(-.2,300.,30.), lWrist(-.2,300.,30.);

	POSEFB rAnkle(2.2,0.).on(part lFoot), lAnkle(2.2,0.).on(part lFoot), rKnee(1.2,0.).on(part lFoot), lKnee(1.2,0.).on(part lFoot), rHip(2.2,0.).on(part lFoot), lHip(2.2,0.).on(part lFoot);
ENDACTIONS
ENDPHASE
ENDSCRIPT
