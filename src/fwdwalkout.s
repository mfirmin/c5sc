SCRIPTS step.t, walk.s;

BEGINSCRIPT fwdhandspring(void)

PHASE 0
> step.t(void);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
	POSE rShoulder(-1.7, 150., 30.);
	POSE lShoulder(-1.7, 150., 30.);
	POSE lKnee(0.05, 300., 30.);
	POSE rKnee(0.5, 300., 30.);
	POSE lHip(0.3, 200., 30.);
	POSE rHip(-1, 200., 30.);
	POSE rAnkle(0, 300., 30.);
	POSE lAnkle(0.4, 300., 30.);
	POSE rElbow(-0.5, 300., 30.);
	POSE lElbow(-0.5, 300., 30.);
ENDACTIONS
TRANSITION to(2).after(time 0.5);
ENDPHASE

PHASE 2
ACTIONS
	POSE waist(0.3, 300., 30.);
	POSE lTorso2uTorso(0.3, 300., 30.);
	POSE rShoulder(-1.8, 300., 30.);
	POSE lShoulder(-1.8, 300., 30.);
	POSE rWrist(-1.5, 300., 30.);
	POSE lWrist(-1.5, 300., 30.);
	POSE lKnee(0.05, 500., 30.);
	POSE rKnee(0.3, 300., 30.);
	POSE rHip(-1.2, 200., 30.);
	POSE lHip(0.3, 200., 30.);
	POSE rAnkle(0.2, 300., 30.);
	POSE lAnkle(0.4, 300., 30.);
	POSE rElbow(-0.2, 300., 30.);
	POSE lElbow(-0.2, 300., 30.);
ENDACTIONS
TRANSITION to(3).after(time 0.2);
ENDPHASE

PHASE 3
ACTIONS
	POSE rShoulder(-2.3, 300., 30.);
	POSE lShoulder(-2.3, 300., 30.);
	POSE rWrist(-1, 300., 30.);
	POSE lWrist(-1, 300., 30.);
	POSE rHip(-1.5, 300., 30.);
	POSE lHip(0.3, 300., 30.);
	POSE rAnkle(0.8, 300., 30.);
ENDACTIONS
TRANSITION to(4).after(contact lHand); 
ENDPHASE

PHASE 4
ACTIONS
	POSE rShoulder(-2.5, 500., 30.);
	POSE lShoulder(-2.5, 500., 30.);
	POSE rElbow(-0.5, 300., 30.);
	POSE lElbow(-0.5, 300., 30.);
	POSE rWrist(-1.5, 300., 30.);
	POSE lWrist(-1.5, 300., 30.);
	POSE rHip(-1.6, 300., 30.);
	POSE lHip(1.6, 300., 200.);
	POSE rKnee(0, 300., 30.);
	POSE lKnee(0, 300., 30.);
	POSE rAnkle(0.4, 300., 30.);
	POSE lAnkle(0, 300., 30.);
ENDACTIONS
TRANSITION to(5).after(time 0.3);
ENDPHASE

PHASE 5
ACTIONS
	POSE waist(-0.2, 300., 100.);
	POSE lTorso2uTorso(-0.2, 300., 100.);
	POSE rShoulder(-2.5, 300., 30.);
	POSE lShoulder(-2.5, 300., 30.);
	POSE rElbow(-0.8, 300., 30.);
	POSE lElbow(-0.8, 300., 30.);
	POSE rWrist(-1.7, 300., 30.);
	POSE lWrist(-1.7, 300., 30.);
	POSE rAnkle(0.2, 300., 30.);
	POSE lAnkle(0.2, 300., 30.);
	POSE rKnee(0.5, 300., 30.);
	POSE lKnee(0.5, 300., 30.);
	POSE rHip(-1.4, 300., 30.);
	POSE lHip(2.3, 300., 200.);
ENDACTIONS
TRANSITION to(6).after(time 0.4);
ENDPHASE

PHASE 6
ACTIONS
	POSE rHip(-0.3, 300., 30.);
	POSE lHip(2, 1000., 100.);
	POSE rKnee(0.4, 300., 30.);
	POSE lKnee(1.4, 300., 30.);
	POSE waist(-0.4, 300., 30.);
	POSE lTorso2uTorso(-0.4, 300., 30.);
	POSE rShoulder(-2.7, 300., 30.);
	POSE lShoulder(-2.7, 300., 30.);
	POSE rAnkle(0.4, 300., 30.);
	POSE lAnkle(-0.8, 300., 30.);
ENDACTIONS
TRANSITION to(7).after(contact lFoot);
ENDPHASE

PHASE 7
ACTIONS
	POSE waist(-0.1, 600., 60.);
	POSE lTorso2uTorso(0, 600., 60.);
	POSE rKnee(1.3, 300., 30.);
	POSE lKnee(0.3, 300., 30.);
	POSE rHip(-0.1, 300., 30.);
	POSE lHip(0.2, 300., 30.);
	POSE rAnkle(-0, 300., 30.);
	POSE lAnkle(-0.7, 300., 30.);
	POSE rShoulder(0, 100., 30.);
	POSE lShoulder(0, 100., 30.);
	POSE rElbow(0, 300., 30.);
	POSE lElbow(0, 300., 30.);
	POSE rWrist(0, 300., 30.);
	POSE lWrist(0, 300., 30.);
ENDACTIONS
TRANSITION to(-1).after(time 1.);
ENDPHASE

PHASE 8
> walk.s(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
