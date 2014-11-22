
SET TORQUELIMIT = 170

BEGINSCRIPT skip(void)

PHASE 0
ACTIONS
	POSE neck2head(0.0), waist(0.0, 600., 60.), uTorso2neck(0.0), lTorso2uTorso(0.0, 600., 60.);
    POSE lWrist(0.0,5,3), rWrist(0.0,5,3);
    POSE rKnee(1.75), lKnee(.19);
    POSE rAnkle(-.2), lAnkle(-.2);

    POSE rShoulder(.3,100,30), rElbow(0,100,30);
    POSE lShoulder(-.3,100,30), lElbow(-.4,100,30);

	VPD uTorso(0.05,300,30.).joint(lHip);
	COMFB2 0. -0.4 j rAnkle
	VPD rThigh(-1.04,-300.,-30).joint(rHip).flags(s);

ENDACTIONS
TRANSITION to(1).after(time .19);
ENDPHASE

PHASE 1
TRANSITION to(2).after(time .12);
ACTIONS
	POSE rKnee(2.18), lKnee(.05);
    POSE lAnkle(1.0);
	VPD uTorso(0.05,300,30.).joint(lHip);
	COMFB2 0. -.4 j rAnkle
	VPD rThigh(-2.25,-300.,-30).joint(rHip).flags(s);
ENDACTIONS
ENDPHASE

PHASE 2
TRANSITION to(3).after(time 0.26);
ACTIONS
	POSE rKnee(2.09), lKnee(.05);
    POSE lAnkle(-.2);
	VPD uTorso(0.05,300,30.).joint(lHip);
	COMFB2 0. -.04 j rAnkle

	VPD rThigh(-2.44,-300.,-30).joint(rHip).flags(s);
ENDACTIONS
ENDPHASE

PHASE 3
TRANSITION to(4).after(contact rFoot);
ACTIONS
	POSE rKnee(.25), lKnee(.10);
    POSE lAnkle(-.2);
	VPD uTorso(0.05,300,30.).joint(lHip);
	COMFB2 -.18 -.37 j rAnkle
	VPD rThigh(.46,-300.,-30).joint(rHip).flags(s);
ENDACTIONS
ENDPHASE


PHASE 4
ACTIONS
    POSE lWrist(0.0,5,3), rWrist(0.0,5,3);

    POSE lKnee(1.75), rKnee(.19);

    POSE lAnkle(-.2), rAnkle(-.2);

    POSE lShoulder(.3,100,30), lElbow(0,100,30);
    POSE rShoulder(-.3,100,30), rElbow(-.4,100,30);

	VPD uTorso(0.05,300,30.).joint(rHip);
	COMFB2 0. -0.4 j lAnkle
	VPD lThigh(-1.04,-300.,-30).joint(lHip).flags(s);

ENDACTIONS
TRANSITION to(5).after(time .19);
ENDPHASE

PHASE 5
TRANSITION to(6).after(time .12);
ACTIONS
	POSE lKnee(2.18), rKnee(.05);
    POSE rAnkle(1.00);
	VPD uTorso(0.05,300,30.).joint(rHip);
	COMFB2 0. -.4 j lAnkle
	VPD lThigh(-2.25,-300.,-30).joint(lHip).flags(s);
ENDACTIONS
ENDPHASE

PHASE 6
TRANSITION to(7).after(time .26);
ACTIONS
	POSE lKnee(2.09), rKnee(.05);
    POSE rAnkle(-.2);
	VPD uTorso(0.05,300,30.).joint(rHip);
	COMFB2 0. -.04 j lAnkle
	VPD lThigh(-2.44,-300.,-30).joint(lHip).flags(s);
ENDACTIONS
ENDPHASE

PHASE 7
ACTIONS
	POSE lKnee(.25), rKnee(.10);
    POSE rAnkle(-.2);
	VPD uTorso(0.05,300,30.).joint(rHip);
	COMFB2 -.18 -.37 j lAnkle
	VPD lThigh(.46,-300.,-30).joint(lHip).flags(s);
ENDACTIONS
TRANSITION to(-1).after(contact lFoot);
ENDPHASE

ENDSCRIPT


