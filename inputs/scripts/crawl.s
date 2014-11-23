SCRIPTS standVFFB.t, crawl.t;

BEGINSCRIPT crawl(void)

PHASE 0
> standVFFB.t(2,2);
TRANSITION to(1).after(complete);
ENDPHASE   

PHASE 1
> crawl.t(5);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
