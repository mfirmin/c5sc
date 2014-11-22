SCRIPTS walkonce.s, fastwalkonce.s, runonce.s, walk2slow2.s, standVFFB.t, skip.s;

BEGINSCRIPT walkcombo(void)

PHASE 0
> walkonce.s(void);
TRANSITION to(1).after(iterations 5);
ENDPHASE

PHASE 1
> skip.s(void);
TRANSITION to(2).after(iterations 2);
ENDPHASE

PHASE 2
> walkonce.s(void);
TRANSITION to(3).after(iterations 3);
ENDPHASE

PHASE 3
> fastwalkonce.s(void);
TRANSITION to(4).after(iterations 5);
ENDPHASE

PHASE 4
> runonce.s(void);
TRANSITION to(5).after(iterations 5);
ENDPHASE

PHASE 5
> fastwalkonce.s(void);
TRANSITION to(6).after(iterations 5);
ENDPHASE

PHASE 6
> walkonce.s(void);
TRANSITION to(7).after(iterations 5);
ENDPHASE

PHASE 7
> walk2slow2.s(void);
TRANSITION to(8).after(complete);
ENDPHASE

PHASE 8
> standVFFB.t(2,2);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
