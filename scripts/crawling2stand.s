SCRIPTS crawl.t, crawl2squat.t, standVFFB.t;

BEGINSCRIPT crawling2stand(void)

PHASE 0
> crawl.t(3);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> crawl2squat.t(void);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> standVFFB.t(2);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
