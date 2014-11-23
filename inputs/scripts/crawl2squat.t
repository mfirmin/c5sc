SCRIPTS crawl.t, hak.t, hak2squat.t, standVFFB.t, squatVFFB.t;

SET TORQUELIMIT = 1000

# Assumes starting from a crawl
BEGINSCRIPT crawl2squat(void)

PHASE 0
ACTIONS
    MATCH rHip.to(lHip).time(1);
    POSE rKnee(2.);
ENDACTIONS
TRANSITION to(1).after(time 1);
ENDPHASE

PHASE 1
ACTIONS
    LIPOSE lAnkle(-0.8).time(1);
    LIPOSE rAnkle(-0.8).time(1);
    LIPOSE rKnee(2.7).time(1);
    LIPOSE lKnee(2.7).time(1);
    LIPOSE lHip(-2.7).time(1);
    LIPOSE rHip(-2.7).time(1);
	POSE lTorso2uTorso(0.5, 600., 60.), uTorso2neck(0.), neck2head(0.);
	POSE waist(0.5,600.,60.);

    
ENDACTIONS
TRANSITION to(2).after(time 1);
ENDPHASE

PHASE 2
ACTIONS

	LIPOSE lTorso2uTorso(0.0, 600., 60.).time(1);
    POSE uTorso2neck(0.), neck2head(0.);
	LIPOSE waist(0.0,600.,60.).time(1);
    LIPOSE lAnkle(-0.8).time(1);
    LIPOSE rAnkle(-0.8).time(1);
    LIPOSE lHip(-2.1).time(1);
    LIPOSE rHip(-2.1).time(1);
	VF (0, -2250, 0).on(rHand).by(rShoulder);
	VF (0, -2250, 0).on(lHand).by(lShoulder);
ENDACTIONS
TRANSITION to(3).after(time .1);
ENDPHASE

PHASE 3
> squatVFFB.t(1);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
