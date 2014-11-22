SCRIPTS stand.t, squat.t, balance2ankle.t;

BEGINSCRIPT vftest(void)

PHASE 0
> stand.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> squat.t(void);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
ACTIONS
	GC uTorso.by(rAnkle);
	GC uTorso.by(lAnkle);
ENDACTIONS
TRANSITION to(3).after(time 10);
ENDPHASE

PHASE 3
> balance2ankle.t(2);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
