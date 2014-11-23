
BEGINSCRIPT walk_on_hands(void)

PHASE 0

ACTIONS
	LIPOSE rHip(0.).time(1);
    LIPOSE lHip(0.).time(1);
	LIPOSE rKnee(0.).time(1);
    LIPOSE lKnee(0.).time(1);
	LIPOSE waist(0.,1000.,60.).time(1.);
	VFFB uTorso(1000., 50.).by(rWrist).over(cop);
	VFFB uTorso(1000., 50.).by(lWrist).over(cop);
ENDACTIONS
TRANSITION to(-1).after(anglerange -2 2);
TRANSITION to(1).after(time 1);
ENDPHASE

PHASE 1

ACTIONS
	VFFB uTorso(2000., 250.).by(lWrist).over(cop);
    LIPOSE rElbow(-1.7).time(1);
ENDACTIONS
TRANSITION to(-1).after(anglerange -2 2.8);
TRANSITION to(2).after(time 1);
ENDPHASE

PHASE 2

ACTIONS
	VFFB uTorso(2000., 250.).by(lWrist).over(lHand);
    LIPOSE rElbow(-.3).time(1);
    LIPOSE rShoulder(-2.9).time(1);
    LIPOSE rWrist(-.5, 300., 30.).time(1);
    LIPOSE lShoulder(-2.5).time(1);
ENDACTIONS
TRANSITION to(-1).after(anglerange -2 2.8);
TRANSITION to(3).after(contact rHand);
ENDPHASE

PHASE 3
ACTIONS
	VFFB uTorso(1000., 1000.).by(lWrist).over(cop);
	VFFB uTorso(1000., 1000.).by(rWrist).over(cop);
ENDACTIONS
TRANSITION to(-1).after(anglerange -2 2.8);
TRANSITION to(4).after(time 1);
ENDPHASE

PHASE 4
ACTIONS
	VFFB uTorso(2000., 200.).by(rWrist).over(rHand);
	VFFB uTorso(300., 30.).by(lWrist).over(rHand);
ENDACTIONS
TRANSITION to(-1).after(anglerange -2 2.8);
TRANSITION to(5).after(time 1);
ENDPHASE

PHASE 5
ACTIONS
    LIPOSE rShoulder(-2.7).time(1);
    LIPOSE rWrist(-1.3,300.,30.).time(1);
	VFFB uTorso(2000., 600.).by(rWrist).over(rHand);
    LIPOSE lElbow(-1.7).time(1);
ENDACTIONS
TRANSITION to(-1).after(anglerange -2 2.8);
TRANSITION to(6).after(time 1);
ENDPHASE


PHASE 6
ACTIONS
	VFFB uTorso(2000., 600.).by(rWrist).over(rHand);
	MATCH lShoulder.to(rShoulder).time(1);
	MATCH lElbow.to(rElbow).time(1);
	MATCH lWrist.to(rWrist, 300., 30.).time(1);
ENDACTIONS
TRANSITION to(-1).after(anglerange -2 2.8);
TRANSITION to(-1).after(time 1);
ENDPHASE

ENDSCRIPT
