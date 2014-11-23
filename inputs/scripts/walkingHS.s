SCRIPTS standVFFB.t, handstand.t, handstand2supine.t, kip.t, handstandwalk.t;

BEGINSCRIPT walking_handstand(void)

PHASE 0
> standVFFB.t(2, 2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> handstand.t(2);
TRANSITION to(-1).after(anglerange -2 2.8);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> handstandwalk.t(void);
TRANSITION to(-1).after(anglerange -2 2.8);
TRANSITION to(3).after(iterations 2);
ENDPHASE

PHASE 3
> handstandwalk.t(void);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 4
> handstand2supine.t(void);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 5
> kip.t(void);
TRANSITION to(-1).after(fallen > 1.5);
TRANSITION to(4).after(fallen < -1.2);
TRANSITION to(6).after(complete);
ENDPHASE

PHASE 6
> standVFFB.t(2);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
