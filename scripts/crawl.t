SCRIPTS stand_to_hak.t, crawl_base_once.t;

BEGINSCRIPT crawl(iters)

PHASE 0
> stand_to_hak.t(void);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> crawl_base_once.t(.3);
TRANSITION to(-1).after(iterations iters);
ENDPHASE

ENDSCRIPT
