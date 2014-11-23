SCRIPTS balancehighsquat.t, squat.t, rise.t, stand.t, squatVFFB.t;

SET TORQUELIMIT = 1000

BEGINSCRIPT backflip(void)

PHASE 0 # Jump!
ACTIONS
	# PDController POSE joint(angle,gains);
	POSE rShoulder(-2.2,300.,30.), lShoulder(-2.2,300.,30.);
	# Virtual Force Controller
	VF (-900,3500,0.).on(uTorso).by(rAnkle);
	VF (-900,3500,0.).on(uTorso).by(lAnkle);
ENDACTIONS
TRANSITION to(1).after(time .2);
ENDPHASE

PHASE 1 # curl in for landing
ACTIONS
	POSE rAnkle(-1), lAnkle(-1);
	POSE rKnee(2.3), lKnee(2.3);
	POSE rHip(-2.), lHip(-2.);
	POSE rShoulder(-2.), lShoulder(-2.);
	POSE rElbow(-1.6), lElbow(-1.6);
	POSE waist(.7), lTorso2uTorso(.7);
ENDACTIONS
#transition after the right foot contacts the ground.
TRANSITION to(2).after(contact rFoot); 
ENDPHASE

PHASE 2 # land and correct
TRANSITION to(4).after(time .2);
ACTIONS
	POSE rAnkle(-.5), lAnkle(-.5);
   	POSE rKnee(2.3,1000.,100.), lKnee(2.3,1000.,100.);
	# apply feedback laws to the ankle joints
	POSEFB rAnkle(2.2,.5).on(part lFoot);
	POSEFB lAnkle(2.2,.5).on(part lFoot);
ENDACTIONS
ENDPHASE

PHASE 3
# switch to balancehighsquat controller
> balancehighsquat.t(5);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 4
> squatVFFB.t(2);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT

