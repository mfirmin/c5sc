BEGINSCRIPT fastrun
PHASE 0
TRANSITION to(1).after(time .2);
ACTIONS
	POSE neck2head(0.0), waist(0.0), uTorso2neck(0.0), lTorso2uTorso(0.0), lWrist(0.0), rWrist(0.0);
	POSE rKnee(2.18), rAnkle(-.2), lKnee(0.05), lAnkle(-.27), rShoulder(.7,100,30), rElbow(-1.9,100,30), lShoulder(-.7,100,30), lElbow(-1.9,100,30);
	VPD uTorso(.14).parent(lThigh);
	COMFB2 0.0 -.2 j lAnkle
	VPD rThigh(-1.08).parent(lThigh);
ENDACTIONS
ENDPHASE

PHASE 1
TRANSITION to(0).after(time 0.2);
ACTIONS
	POSE lKnee(2.18), lAnkle(-.2), rKnee(0.05), rAnkle(-.27), lShoulder(.7,100,30), lElbow(-1.9,100,30), rShoulder(-.7,100,30), rElbow(-1.9,100,30);
	VPD uTorso(.14).parent(rThigh);
	COMFB2 0.0 -.2 j rAnkle
	VPD lThigh(-1.08).parent(rThigh);
ENDACTIONS
ENDPHASE
ENDSCRIPT
