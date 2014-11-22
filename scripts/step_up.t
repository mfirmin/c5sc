SCRIPTS standVFFB.t;

BEGINSCRIPT step_up(x, y)

PHASE 0
> standVFFB.t(.1, .1);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
	IK rFoot.targetlocal(0.1, -.6, 0).base(rHip);
	VFFB uTorso(3000., 250.).by(lAnkle).over(cop);
ENDACTIONS
TRANSITION to(2).after(time .2);
ENDPHASE

PHASE 2
ACTIONS
	IK rFoot.targetglobal(x, y, -10).base(rHip).tolerance(0.001);
	VPD rFoot(0.0, -300, -30).joint(rAnkle);
	VFFB uTorso(3000., 250.).by(lAnkle).over(lFoot);
ENDACTIONS
TRANSITION to(3).after(time .3);
ENDPHASE

PHASE 3
ACTIONS
	LIPOSE rHip(0.0).time(5);
	VPD rFoot(0.0, -1000, -100).joint(rAnkle);
	VFFB uTorso(3000, 250.).by(lAnkle).over(lFoot);
ENDACTIONS
TRANSITION to(4).after(contact rFoot);
ENDPHASE

PHASE 4
ACTIONS
   	VFFB uTorso(1000, 400.).by(lAnkle).over(rFoot);
   	VPD uTorso(0.0, 100, 10).joint(rHip);
   	POSE rAnkle(0., 0., 100);
ENDACTIONS
TRANSITION to(5).after(time 1);
ENDPHASE

PHASE 5
ACTIONS
  	  LIPOSE lAnkle(.05).time(.2);
      VFFB uTorso(1200, 400.).by(rAnkle).over(rFoot);
  	  VPD uTorso(0.1,400,40).joint(rHip);
ENDACTIONS
TRANSITION to(6).after(time .2);
ENDPHASE

PHASE 6
ACTIONS
	LIPOSE rKnee(0).time(1);
	LIPOSE lKnee(1.2).time(1);
	LIPOSE rHip(-0.0).time(1);
	LIPOSE lHip(-0.0).time(1);
    LIPOSE rAnkle(-0.2).time(1);
    LIPOSE lAnkle(.2).time(1);
	VFFB uTorso(2200, 750.).by(rAnkle).over(rFoot);
ENDACTIONS
TRANSITION to(7).after(time 1);
ENDPHASE

PHASE 7
ACTIONS
	LIPOSE lHip(-.6).time(1.);
  	LIPOSE lAnkle(-.4).time(1);
  	LIPOSE rAnkle(-0.05).time(1);
	VFFB uTorso(2000,400.).by(rAnkle).over(rFoot);
ENDACTIONS
TRANSITION to(8).after(time 1);
ENDPHASE

PHASE 8
ACTIONS
	MATCH lKnee.to(rKnee).time(1);
	MATCH lHip.to(rHip).time(1);
	MATCH lAnkle.to(rAnkle).time(1);

	LIPOSE rShoulder(0.0).time(1);
	LIPOSE lShoulder(0.0).time(1);

	POSE rAnkle(0.0,1000.,100.);

	VFFB uTorso(1000,250.).by(rAnkle).over(rFoot);
ENDACTIONS
TRANSITION to(-1).after(time 1);
ENDPHASE

ENDSCRIPT

