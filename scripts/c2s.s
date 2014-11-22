SCRIPTS crawl2squat.t, standVFFB.t;

BEGINSCRIPT c2s(void)

PHASE 0
LOAD beforec2s.sav;
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> crawl2squat.t(void);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> standVFFB.t(2,2);
TRANSITION to(-1).after(complete);
ENDPHASE


ENDSCRIPT
