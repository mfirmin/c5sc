SCRIPTS standVFFB.t, handstand.t, handstand2supine.t, kip.t;

BEGINSCRIPT handstand(void)

PHASE 0
> standVFFB.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> handstand.t(2);
TRANSITION to(-1).after(anglerange -2 2);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> handstand2supine.t(void);
TRANSITION to(-1).after(anglerange 0 3);
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 3
> kip.t(void);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 4
> standVFFB.t(2);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
