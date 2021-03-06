BEGINSCRIPT simbiconfb(dt, cde, cdo, cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle, spd, spdgain)

PHASE 0
ACTIONS
	POSE neck2head(0.0), waist(0.0, 600., 60.), uTorso2neck(0.0), lTorso2uTorso(0.0, 600., 60.), lWrist(0.0,5,3), rWrist(0.0,5,3), rKnee(swke), rAnkle(ankle), lKnee(stke), lAnkle(ankle), rShoulder(.1,100,30), rElbow(0,100,30), lShoulder(-.1,100,30), lElbow(-.3,100,30);
	VPD uTorso(tor,300,30.).joint(lHip);
	COMFB2 cde cve j rAnkle
	VPD rThigh(swhe,-300.,-30).joint(rHip).flags(s);
    VFSFB uTorso(spdgain).by(lAnkle).speed(spd);
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
    VFSFB uTorso(spdgain).by(lAnkle).speed(spd);
ENDACTIONS
ENDPHASE

PHASE 2
TRANSITION to(3).after(time dt);
ACTIONS
	POSE lKnee(swke), rShoulder(-.1,100,30), rElbow(-.3,100,30), lShoulder(.1,100,30), lElbow(0,100,30);
	VPD uTorso(tor,300,30.).joint(rHip);
	COMFB2 cde cve j lAnkle
	VPD lThigh(swhe,-300.,-30).joint(lHip).flags(s);
    VFSFB uTorso(spdgain).by(rAnkle).speed(spd);
ENDACTIONS
ENDPHASE

PHASE 3
TRANSITION to(0).after(contact lFoot);
ACTIONS
	POSE lKnee(swko), rKnee(stko);
	VPD uTorso(tor,300,30.).joint(rHip);
	COMFB2 cdo cvo j lAnkle
	VPD lThigh(swho,-300.,-30).joint(lHip).flags(s);
    VFSFB uTorso(spdgain).by(rAnkle).speed(spd);
ENDACTIONS
ENDPHASE
ENDSCRIPT
