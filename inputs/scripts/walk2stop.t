BEGINSCRIPT stop(cde, cve)

PHASE 0
TRANSITION to(1).after(time .3);
ACTIONS
	POSE neck2head(0.0), waist(0.0, 600., 60.), uTorso2neck(0.0), lTorso2uTorso(0.0, 600., 60.);
    POSE lWrist(0.0,5,3), rWrist(0.0,5,3);
    POSE rKnee(.7), rAnkle(-0.5);
    POSE lKnee(.1);
    POSE lAnkle(-0.2);
	VPD uTorso(0,300,30.).joint(lHip);
	COMFB2 cde cve j rAnkle
	VPD rThigh(-.5,-300.,-30).joint(rHip).flags(s);
ENDACTIONS
ENDPHASE

PHASE 1
TRANSITION to(2).after(time 1);
ACTIONS
	POSE rAnkle(0.0);
    POSE rHip(0.0,1000.,100.);
    POSE lHip(-0.5,1000.,100.);
	POSE rKnee(0.0);
	POSE lKnee(1.3);
	POSE lAnkle(-0.5);
	VFFB uTorso(1000., 450.).by(rAnkle).over(rFoot);
	VPD uTorso(0,300,30.).joint(rHip);
ENDACTIONS
ENDPHASE

PHASE 2
TRANSITION to(3).after(time 1);
ACTIONS
	POSE neck2head(0.0), waist(0.0, 600., 60.), uTorso2neck(0.0), lTorso2uTorso(0.0, 600., 60.);
	POSE rAnkle(-0.);
	POSE rKnee(0.0);
    POSE rHip(0.0);
	POSE lAnkle(-0.9);
	VFFB uTorso(1000., 450.).by(rAnkle).over(cop);
ENDACTIONS
ENDPHASE

PHASE 3
TRANSITION to(-1).after(time 2);
ACTIONS
	POSE rAnkle(-0.05);
    MATCH lAnkle.to(rAnkle).time(1);
    MATCH lHip.to(rHip).time(1);
    MATCH lKnee.to(rKnee).time(1);
	VFFB uTorso(1000., 450.).by(rAnkle).over(cop);
ENDACTIONS
ENDPHASE

ENDSCRIPT
