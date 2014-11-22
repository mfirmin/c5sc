SCRIPTS balancehighsquat.t, squat.t, rise.t;


BEGINSCRIPT hop(void)

PHASE 0
TRANSITION to(1).after(time 2);
ACTIONS
	POSE rAnkle(-.4), lAnkle(-.4), lKnee(1.3,120.,70.), rKnee(1.3,120.,70.), rHip(-1.4,800.,200.), lHip(-1.4,800.,200.), rShoulder(-0.,100.,30.), lShoulder(-0.,100.,30.), rElbow(-1.7,100.,30.), lElbow(-1.7,100.,30.);
	POSEFB rAnkle(6.2,.5).on(joint lAnkle), lAnkle(6.2,.5).on(joint lAnkle), rHip(-2.2,-.5).on(joint lAnkle), lHip(-2.2,-.5).on(joint lAnkle);
ENDACTIONS
ENDPHASE


PHASE 1 # Jump!
TRANSITION to(2).after(time .2);
ACTIONS
	POSE rShoulder(-2.9,100.,30.), lShoulder(-2.9,100.,30.), rElbow(0.0), lElbow(0.);
	SVF(0., -800., 0.).on(uTorso).by(rHip);
	SVF(0., -800., 0.).on(uTorso).by(lHip);
	SVF(0., -1000., 0.).on(uTorso).by(rKnee);
	SVF(0., -1000., 0.).on(uTorso).by(lKnee);
ENDACTIONS
ENDPHASE

PHASE 2 # do nothing
TRANSITION to(3).after(contact rFoot);
ACTIONS
	POSE rShoulder(0.), lShoulder(0.);
	POSE rAnkle(-.5), lAnkle(-.5), lKnee(1.1,300.,40.), rKnee(1.1,300.,40.), rHip(-.5,500.,50.), lHip(-.5,500.,50.), rShoulder(-0.,100.,30.), lShoulder(-0.,100.,30.), rElbow(-1.7,100.,30.), lElbow(-1.7,100.,30.);
ENDACTIONS
ENDPHASE

PHASE 3
> balancehighsquat.t(4);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 4
> squat.t(void);
TRANSITION to(5).after(complete);
ENDPHASE

PHASE 5
> rise.t(void);
TRANSITION to(-1).after(complete);
ENDPHASE
ENDSCRIPT
