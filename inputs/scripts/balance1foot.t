
# balances above ankle on 1 foot

BEGINSCRIPT balance1foot(dt)
PHASE 0
TRANSITION to(-1).after(time dt);
ACTIONS 
        POSE waist(0.0,600.,30.), neck2head(0.0), uTorso2neck(0.0), lTorso2uTorso(0.0,600.,30.);

       	POSE rShoulder(0.,150.,80.), lShoulder(0.,150.,80.);
	POSE rElbow(0.0), lElbow(0.0);
        POSE rWrist(0.0), lWrist(0.0);

        POSE rAnkle(0.,1000.,100.), lAnkle(0.,150.,90.);
       	POSE rKnee(0.0,300.,200.), lKnee(2.2,300.,200.);
        POSE rHip(0.,300.,60.), lHip(-.7,300.,60.);

	POSEFB rAnkle(2.2,.5).on(part rFoot);
ENDACTIONS
ENDPHASE
ENDSCRIPT
