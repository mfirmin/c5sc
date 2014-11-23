SCRIPTS skip.s, walkonce.s, skipOptimized.s;

BEGINSCRIPT cs(void)

PHASE 0
	LOAD beforeskipOpt.sav;
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> skip.s(void);
TRANSITION to(2).after(iterations 2);
ENDPHASE

PHASE 2
> skipOptimized.s(void);
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 3
> walkonce.s(void);
TRANSITION to(4).after(iterations 10);
ENDPHASE

PHASE 4
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
