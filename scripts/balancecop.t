BEGINSCRIPT balancecop(dt)
PHASE 0
TRANSITION to(-1).after(time dt);
ACTIONS
	POSE rElbow(0.0), lElbow(0.0), rWrist(0.0), lWrist(0.0), neck2head(0.0), uTorso2neck(0.0), waist(0.0), lTorso2uTorso(0.0);
	POSE rKnee(.5), rAnkle(0), lKnee(0.05), lAnkle(-.2), rShoulder(.1,100,30), lShoulder(-.1,100,30);
	VPD uTorso(0.0).parent(lThigh);
	VPD rThigh(-0.4).parent(lThigh);
ENDACTIONS
ENDPHASE
ENDSCRIPT
