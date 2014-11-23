SCRIPTS standVFFB.t, fwdhandspring.t, balance1foot.t, walk.t;

BEGINSCRIPT fwdhandspring(void)

PHASE 0
> standVFFB.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> fwdhandspring.t(void);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 2
> balance1foot.t(2);
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 3
> standVFFB.t(1);
TRANSITION to(-1).after(complete);
ENDPHASE

PHASE 4
> walk.t(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
