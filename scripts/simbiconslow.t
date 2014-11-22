
BEGINSCRIPT simbiconslow(dt, cde, cdo, cve, cvo, tor, swhe, swho, swke, swko, stke, stko, ankle, KP, KD)

PHASE 0
ACTIONS
	POSE neck2head(0.0), waist(0.0, 600., 60.), uTorso2neck(0.0), lTorso2uTorso(0.0, 600., 60.), lWrist(0.0,5,3), rWrist(0.0,5,3), rShoulder(.1,100,30), rElbow(0,100,30), lShoulder(-.1,100,30), lElbow(-.3,100,30);
	POSE rKnee(swke, KP, KD), lKnee(stke, KP, KD);
	POSE rAnkle(ankle, KP, KD), lAnkle(ankle, KP, KD);
	VPD uTorso(tor, KP, KD).parent(lThigh);
	COMFB2 cde cve j rAnkle
	VPD rThigh(swhe, KP, KD).parent(lThigh);
ENDACTIONS
TRANSITION to(1).after(time dt);
ENDPHASE

PHASE 1
TRANSITION to(2).after(contact rFoot);
ACTIONS
	POSE rKnee(swko, KP, KD), lKnee(stko, KP, KD);
	VPD uTorso(tor, KP, KD).parent(lThigh);
	COMFB2 cdo cvo j rAnkle
	VPD rThigh(swho, KP, KD).parent(lThigh);
ENDACTIONS
ENDPHASE

PHASE 2
TRANSITION to(3).after(time dt);
ACTIONS
	POSE lKnee(swke, KP, KD);
	POSE rShoulder(-.1,100,30), rElbow(-.3,100,30), lShoulder(.1,100,30), lElbow(0,100,30);
	VPD uTorso(tor, KP, KD).parent(rThigh);
	COMFB2 cde cve j lAnkle
	VPD lThigh(swhe, KP, KD).parent(rThigh);
ENDACTIONS
ENDPHASE

PHASE 3
TRANSITION to(0).after(contact lFoot);
ACTIONS
	POSE lKnee(swko, KP, KD), rKnee(stko, KP, KD);
	VPD uTorso(tor, KP, KD).parent(rThigh);
	COMFB2 cdo cvo j lAnkle
	VPD lThigh(swho, KP, KD).parent(rThigh);
ENDACTIONS
ENDPHASE
ENDSCRIPT
