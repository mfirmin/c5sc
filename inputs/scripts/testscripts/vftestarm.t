SCRIPTS balance2ankle.t;

BEGINSCRIPT vftest(void)

PHASE 0
> balance2ankle.t(0);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
	VF (2,0.,0.).on(uTorso).by(rAnkle);
	VF (2,0,0).on(uTorso).by(lAnkle);
ENDACTIONS
TRANSITION to(-1).after(time 50);
ENDPHASE

ENDSCRIPT


