SCRIPTS standVFFB.t, handstand.t;

BEGINSCRIPT stand2handstand(dt)

PHASE 0
> standVFFB.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> handstand.t(dt);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
