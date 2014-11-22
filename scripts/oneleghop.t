SCRIPTS walk.s, walkonce.s;

BEGINSCRIPT hop(void)
PHASE 0
TRANSITION to(1).after(time .4);
ACTIONS
	POSE neck2head(0.0), lTorso2uTorso(0.0, 600., 30.), uTorso2neck(0.0), waist(0.0, 600., 30.), rWrist(0.0), lWrist(0.0), rKnee(0.9), rAnkle(-0.2), lKnee(0.05), lAnkle(-0.2), rShoulder(.1,100.,30.), rElbow(0,100.,30.), lShoulder(-.1,100.,30.), lElbow(-.3, 100., 30.), rHip(-.7), lHip(0.0);
ENDACTIONS
ENDPHASE

PHASE 1
TRANSITION to(2).after(contact rFoot);
ACTIONS
	POSE rKnee(.7), rAnkle(-.2), lKnee(0.05), lAnkle(0.0), rShoulder(.1,100.,30.), rElbow(0,100.,30.), lShoulder(-.1,100.,30.), lElbow(-.3,100.,30.), rHip(-.6), lHip(.4,200.,90.);
ENDACTIONS
ENDPHASE

PHASE 2
ACTIONS
    POSE lTorso2uTorso(0.0, 600., 60.), uTorso2neck(0.0), waist(0.0, 600., 60.);
	VFFB uTorso(1250., 300.).by(rAnkle).over(rFoot);
    LIPOSE lHip(-.6).time(.5);
    LIPOSE lKnee(1.4).time(.5);
    VPD uTorso(0.2).joint(rHip);
    POSE rAnkle(-.6);
    POSE rHip(0.1);
    POSE rKnee(0.1);
ENDACTIONS
TRANSITION to(3).after(time .5);
ENDPHASE

PHASE 3
ACTIONS
    POSE rAnkle(1.2,1000.,100.);
ENDACTIONS
    TRANSITION to(4).after(nocontact rFoot);
ENDPHASE

PHASE 4
ACTIONS
    POSE lHip(-0.1);
    POSE lKnee(0.0);
    POSE lAnkle(0.0);

    POSE rHip(-0.7);
    POSE rKnee(0.1);
    POSE rAnkle(0.0);
ENDACTIONS
    TRANSITION to(6).after(contact lFoot);
ENDPHASE

PHASE 5
ACTIONS
    POSE rHip(-.2);
    POSE rKnee(.1);
    POSE rAnkle(.0);
	VFFB uTorso(2250., 300.).by(rAnkle).over(cop);
	VFFB uTorso(2250., 300.).by(rAnkle).over(cop);
ENDACTIONS
    TRANSITION to(6).after(time .2);
ENDPHASE

PHASE 6
> walkonce.s(void);
TRANSITION to(0).after(iterations 5);
ENDPHASE

ENDSCRIPT
