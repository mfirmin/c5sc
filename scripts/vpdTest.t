SCRIPTS standVFFB.t;

BEGINSCRIPT STANDINGPOSE(void)

PHASE 0
> standVFFB.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
    VPD uTorso(0.0,300.,6.).joint(lHip);
    VPD rThigh(0.40,-100.,-10.).joint(rHip);
    POSE rKnee(1.5);
ENDACTIONS
TRANSITION to(-1).after(time 50);
ENDPHASE

ENDSCRIPT
