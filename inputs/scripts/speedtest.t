SCRIPTS standVFFB.t;

BEGINSCRIPT spdtest(speed)

PHASE 0
> standVFFB.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
    VFSFB uTorso(1000).by(rAnkle).speed(0.3);
    VFSFB uTorso(1000).by(lAnkle).speed(0.3);
ENDACTIONS
TRANSITION to(-1).after(time 50);
ENDPHASE

ENDSCRIPT
