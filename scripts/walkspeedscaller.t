SCRIPTS walkspeeds.t;

BEGINSCRIPT walkspeedscaller(void)

PHASE 0
> walkspeeds.t(.3);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
