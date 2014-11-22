SCRIPTS balance1foot.t, 1foot2stand.t, standVFFB.t;

BEGINSCRIPT 1foot(void)

PHASE 0
> balance1foot.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> 1foot2stand.t(2);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> standVFFB.t(2);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
