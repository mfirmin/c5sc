SCRIPTS squatVFFB.t, supine.t;

BEGINSCRIPT fallback(void)
PHASE 0
> squatVFFB.t(1);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1 # fall back
ACTIONS
	VF (-200,0,0).on(uTorso).by(rAnkle);
	VF (-200,0,0).on(uTorso).by(lAnkle);
ENDACTIONS
TRANSITION to(2).after(contact uTorso);

ENDPHASE

PHASE 2 # lie down
> supine.t(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
