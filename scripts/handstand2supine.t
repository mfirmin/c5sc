SCRIPTS stand2handstand.t;

BEGINSCRIPT supine(void)

PHASE 0
ACTIONS
	LIPOSE rShoulder(-2.).time(1);
	LIPOSE lShoulder(-2.).time(1);
	LIPOSE rElbow(-1.57).time(1);
	LIPOSE lElbow(-1.57).time(1);
	LIPOSE rWrist(-1.57,300,30.).time(1);
	LIPOSE lWrist(-1.57,300.,30.).time(1);
	POSE rHip(-1.57), lHip(-1.57);
	LIPOSE neck2head(1.).time(1);
	LIPOSE uTorso2neck(1.).time(1);
	LIPOSE waist(1.).time(1);
	LIPOSE lTorso2uTorso(1.).time(1);
ENDACTIONS
TRANSITION to(-1).after(anglerange 0 3);
TRANSITION to(1).after(time 1.2);
ENDPHASE

PHASE 1
ACTIONS
	POSE neck2head(0.0), uTorso2neck(0.0), waist(0.0,600.,60.), lTorso2uTorso(0.0,600.,60.);
	POSE rShoulder(0.0), lShoulder(0.0);
	POSE rElbow(0.0), lElbow(0.0);
	POSE rWrist(0.0), lWrist(0.0);

	POSE rHip(0.0), lHip(0.0);
	POSE rKnee(0.0), lKnee(0.0);
	POSE rAnkle(0.0), lAnkle(0.0);
ENDACTIONS
TRANSITION to(-1).after(anglerange 0 3);
TRANSITION to(-1).after(time 1);
ENDPHASE

ENDSCRIPT
