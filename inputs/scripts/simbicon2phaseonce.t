BEGINSCRIPT simbicon(dt, cde, cdo, cve, cvo, tor, swh, swk, stk, swa, sta)

PHASE 0
ACTIONS
	POSE neck2head(0.0), waist(0.0), uTorso2neck(0.0), lTorso2uTorso(0.0), lWrist(0.0,5,3), rWrist(0.0,5,3), rKnee(swk), rAnkle(swa), lKnee(stk), lAnkle(sta), rShoulder(.1,100,30), rElbow(-1.7,100,30), lShoulder(-.1,100,30), lElbow(-1.7,100,30);
	VPD uTorso(tor,300,30.).joint(lHip);
	COMFB2 cde cve j rAnkle
	VPD rThigh(swh,-300.,-30).joint(rHip).flags(s);
ENDACTIONS
TRANSITION to(1).after(time dt);
ENDPHASE

PHASE 1
ACTIONS
	POSE lKnee(swk), rKnee(stk), lAnkle(swa), rAnkle(sta), rShoulder(-.1,100,30), rElbow(-1.7,100,30), lShoulder(.1,100,30), lElbow(-1.7,100,30);
	VPD uTorso(tor,300,30.).joint(rHip);
	COMFB2 cde cve j lAnkle
	VPD lThigh(swh,-300.,-30).joint(lHip).flags(s);
ENDACTIONS
TRANSITION to(-1).after(time dt);
ENDPHASE
ENDSCRIPT
