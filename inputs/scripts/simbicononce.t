BEGINSCRIPT simbicon(dt, cde, cdo, cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle)

PHASE 0
ACTIONS
	POSE neck2head(0.0), uTorso2neck(0.0);
        POSE waist(0.0, 600., 60.), lTorso2uTorso(0.0, 600., 60.);
        POSE lWrist(0.0,5,3), rWrist(0.0,5,3);
        POSE rKnee(swke), rAnkle(ankle);
        POSE lKnee(stke), lAnkle(ankle);
        POSE rShoulder(.3,100,30), rElbow(0,100,30);
        POSE lShoulder(-.3,100,30), lElbow(-.4,100,30);
	VPD uTorso(tor,300,30.).joint(lHip);
	COMFB2 cde cve j rAnkle
	VPD rThigh(swhe,-300.,-30).joint(rHip).flags(s);
ENDACTIONS
TRANSITION to(1).after(time dt);
ENDPHASE

PHASE 1
TRANSITION to(2).after(contact rFoot);
ACTIONS
	POSE rKnee(swko), lKnee(stko);
	VPD uTorso(tor,300,30.).joint(lHip);
	COMFB2 cdo cvo j rAnkle
	VPD rThigh(swho,-300.,-30).joint(rHip).flags(s);
ENDACTIONS
ENDPHASE

PHASE 2
TRANSITION to(3).after(time dt);
ACTIONS
	POSE lKnee(swke), rShoulder(-.3,100,30), rElbow(-.4,100,30), lShoulder(.3,100,30), lElbow(0,100,30);
	VPD uTorso(tor,300,30.).joint(rHip);
	COMFB2 cde cve j lAnkle
	VPD lThigh(swhe,-300.,-30).joint(lHip).flags(s);
ENDACTIONS
ENDPHASE

PHASE 3
TRANSITION to(-1).after(contact lFoot);
ACTIONS
	POSE lKnee(swko), rKnee(stko);
	VPD uTorso(tor,300,30.).joint(rHip);
	COMFB2 cdo cvo j lAnkle
	VPD lThigh(swho,-300.,-30).joint(lHip).flags(s);
ENDACTIONS
ENDPHASE
ENDSCRIPT
