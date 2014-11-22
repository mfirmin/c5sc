SCRIPTS standVFFB.t;

BEGINSCRIPT envtest(void)

PHASE 0
> standVFFB.t(1);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
	IK rFoot.targetlocal(0.1, -.3, 0).base(rHip);
	VFFB uTorso(3000., 250.).by(lAnkle).over(cop);
ENDACTIONS
TRANSITION to(2).after(time .3);
ENDPHASE

PHASE 2
ACTIONS
	IK rFoot.targetglobal(.4, .51, -10).base(rHip).tolerance(0.001);
	VPD rFoot(0.0, 1000, 100).parent(rShin);
	VFFB uTorso(3000., 250.).by(lAnkle).over(lFoot);
ENDACTIONS
TRANSITION to(3).after(time .3);
ENDPHASE

PHASE 3
ACTIONS
	LIPOSE rHip(0.0).time(2);
	VFFB uTorso(3000, 250.).by(lAnkle).over(lFoot);
ENDACTIONS
TRANSITION to(4).after(contact rFoot);
ENDPHASE

PHASE 4
ACTIONS
	POSE rAnkle(-.4), lAnkle(-.2);
	LIPOSE rKnee(2.).time(2);
	POSE rHip(-1.4,0.0,100.0);
	POSE rShoulder(-1.57), lShoulder(-1.57);
ENDACTIONS
TRANSITION to(5).after(time 3);
ENDPHASE

PHASE 5
ACTIONS
	LIPOSE lAnkle(.8).time(1);
	LIPOSE rKnee(0).time(2);
# start lifting up just to pull lFoot off ground
ENDACTIONS
TRANSITION to(6).after(time .2);
ENDPHASE

PHASE 6
ACTIONS
	LIPOSE rKnee(0).time(2);
	LIPOSE lKnee(1.5).time(2);
	LIPOSE rHip(0.0).time(2.);
	LIPOSE lHip(-0.0).time(2.);
	VFFB uTorso(3000, 250.).by(rAnkle).over(rFoot);
ENDACTIONS
TRANSITION to(7).after(time 2);
ENDPHASE

PHASE 7
ACTIONS
	LIPOSE lHip(-1.).time(1.);
	VFFB uTorso(3000,250.).by(rAnkle).over(rFoot);
ENDACTIONS
TRANSITION to(8).after(time 1);
ENDPHASE

PHASE 8
ACTIONS
	MATCH lKnee.to(rKnee);
	MATCH lHip.to(rHip);
	MATCH lAnkle.to(rAnkle);

	LIPOSE rShoulder(0.0).time(2);
	LIPOSE lShoulder(0.0).time(2);

	POSE rAnkle(0.0,1000.,100.);

	VFFB uTorso(3000,250.).by(rAnkle).over(rFoot);
ENDACTIONS
TRANSITION to(-1).after(time 4);
ENDPHASE

ENDSCRIPT
