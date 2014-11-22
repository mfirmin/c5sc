SCRIPTS squatVFFB.t, backflip.t, standVFFB.t, somersault.t, fwdhandspring.s, walk2stop.t, standVFFB.t, walkcombo.s, crawl.s, hak.t, hak2squat.t, crawl2squat.t, handstand.s, handstand2supine.t, supine.t, kip.t, walkinghandstand.s, fwdhop.s;


BEGINSCRIPT longcombo(void)
	
PHASE 0
> squatVFFB.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
> backflip.t(void);
TRANSITION to(8).after(fallen > 1.0);
TRANSITION to(2).after(complete);
ENDPHASE

PHASE 2
> standVFFB.t(1.5,1.5);
TRANSITION to(3).after(complete);
ENDPHASE

PHASE 3
> fwdhop.s(void);
TRANSITION to(-1).after(fallen x .6);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 4
> standVFFB.t(2,2);
TRANSITION to(5).after(complete);
ENDPHASE

PHASE 5
> fwdhandspring.s(void);
TRANSITION to(6).after(complete);
ENDPHASE

PHASE 6
> walkcombo.s(void);
TRANSITION to(7).after(complete);
ENDPHASE

PHASE 7
> standVFFB.t(2,2);
TRANSITION to(8).after(complete);
ENDPHASE

PHASE 8
> crawl.s(void);
TRANSITION to(9).after(complete);
ENDPHASE

PHASE 9
> crawl2squat.t(void);
TRANSITION to(10).after(complete);
ENDPHASE

PHASE 10
> standVFFB.t(2,2);
TRANSITION to(11).after(complete);
ENDPHASE

PHASE 11
> walkinghandstand.s(void);
TRANSITION to(8).after(fallen > .6);
TRANSITION to(12).after(complete);
ENDPHASE

PHASE 12
> squatVFFB.t(2);
TRANSITION to(13).after(complete);
ENDPHASE

PHASE 13
> standVFFB.t(1.5,1.5);
TRANSITION to(5).after(complete);
ENDPHASE

PHASE 14
> fwdhop.s(void);
TRANSITION to(15).after(complete);
ENDPHASE

PHASE 15
> standVFFB.t(1.,1.);
TRANSITION to(0).after(complete);
ENDPHASE

ENDSCRIPT
