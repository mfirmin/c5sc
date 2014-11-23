SCRIPTS standVFFB.t;

BEGINSCRIPT prone2stand(void)

PHASE 0
> standVFFB.t(0);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
    EF uTorso(100.0, .0, .0);
ENDACTIONS
TRANSITION to(2).after(time 2);

ENDPHASE

PHASE 2
ACTIONS
    POSE rShoulder(.7), lShoulder(.7);
    POSE rElbow(-2.4), lElbow(-2.4);
    POSE rWrist(-1.8), lWrist(-1.8);
ENDACTIONS
TRANSITION to(3).after(time 1);
ENDPHASE

PHASE 3
ACTIONS
POSE waist(0,1000.,10.);
POSE lTorso2uTorso(0,1000.,10.);
    LIPOSE rShoulder(-1.87).time(1.);
    LIPOSE lShoulder(-1.87).time(1.);
    LIPOSE rElbow(0).time(1.);
    LIPOSE lElbow(0).time(1.);
    LIPOSE rWrist(-1.57,300.,30.).time(1.);
    LIPOSE lWrist(-1.57,300.,30.).time(1.);
    LIPOSE rHip(-2.47).time(1.);
    LIPOSE lHip(-2.47).time(1.);
    LIPOSE rKnee(1.).time(1.);
    LIPOSE lKnee(1.).time(1.);
ENDACTIONS
TRANSITION to(4).after(time 1.);
ENDPHASE

PHASE 4
ACTIONS
    LIPOSE rKnee(1.5).time(1.);
    LIPOSE rHip(-2.9).time(1.);
ENDACTIONS
    TRANSITION to(5).after(time 1.);
ENDPHASE

PHASE 5
ACTIONS
    LIPOSE rKnee(0.).time(1.);
ENDACTIONS
    TRANSITION to(-1).after(time 1.);
ENDPHASE


ENDSCRIPT
