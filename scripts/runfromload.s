SCRIPTS run.t;

BEGINSCRIPT run(void)

PHASE 0

LOAD runstart.sav;
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> run.t(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT
