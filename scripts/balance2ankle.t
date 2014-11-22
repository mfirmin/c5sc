
# balances above ankle

BEGINSCRIPT balanceankle(dt)
PHASE 0
TRANSITION to(-1).after(time dt);
ACTIONS 
	#POSE format: POSE(<angle>, [kp, kd])
	POSE rElbow(0.0), lElbow(0.0), rWrist(0.0), lWrist(0.0), waist(0.0,600.,30.), neck2head(0.0), uTorso2neck(0.0), lTorso2uTorso(0.0,600.,30.), rKnee(0.0,300.,200.), lKnee(0.,300.,200.), rHip(0.,300.,60.), lHip(0.,300.,60.), rShoulder(0.,150.,80.), lShoulder(0.,150.,80.), rAnkle(0.,150.,90.), lAnkle(0.,150.,90.);
	#POSE feedback, using center of mass feedback.
	# Format: joint(<cd>, <cv>).on(<joint|part> <jointname|partname>
	POSEFB rAnkle(2.2,.5).on(joint lAnkle), lAnkle(2.2,.5).on(joint lAnkle);
ENDACTIONS
ENDPHASE
ENDSCRIPT
