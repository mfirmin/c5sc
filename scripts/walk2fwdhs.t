SCRIPTS walkcombo.t, stand.t, fwdhandspring.t;

BEGINSCRIPT w2fhs(void)

PHASE 0
> walkcombo.t(void);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> stand.t(5);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> fwdhandspring.t(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
