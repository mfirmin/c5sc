SCRIPTS squatVFFB.t, backflip.t, standVFFB.t, somersault.t, fwdhandspring.s, walk2stop.t, standVFFB.t, walkcombo.s, crawl.s, hak.t, hak2squat.t, crawl2squat.t, handstand.s, handstand2supine.t, supine.t, kip.t, walkinghandstand.s, fwdhop.s, skipOptimized.s, walk2stopOPT.s, walk2slow2.s;


BEGINSCRIPT longcombo(void)

PHASE 0
> standVFFB.t(2, 2);
TRANSITION to(3).after(fallen > 1.0);
TRANSITION to(14).after(random .25);
TRANSITION to(5).after(random .3333333);
TRANSITION to(3).after(random .5);
TRANSITION to(1).after(random 1);
ENDPHASE

PHASE 1
> squatVFFB.t(2);
TRANSITION to(3).after(fallen > 1.2);
TRANSITION to(0).after(random .5);
TRANSITION to(2).after(random 1);
ENDPHASE

PHASE 2
> backflip.t(void);
TRANSITION to(0).after(complete);
ENDPHASE

PHASE 3
> crawl.s(void);
TRANSITION to(4).after(complete);
ENDPHASE

PHASE 4
SAVE beforec2s.sav;
TRANSITION to(16).after(complete);
ENDPHASE

PHASE 5
> fwdhandspring.s(void);
TRANSITION to(6).after(complete);
ENDPHASE

PHASE 6
> walkonce.s(void);
TRANSITION to(7).after(iterations 5);
ENDPHASE

PHASE 7
TRANSITION to(10).after(random .33333333);
TRANSITION to(8).after(random .5);
TRANSITION to(9).after(random 1);
ENDPHASE

PHASE 8
SAVE atskip.sav;
TRANSITION to(15).after(complete);
ENDPHASE

PHASE 9
> walk2slow2.s(void);
TRANSITION to(0).after(complete);
ENDPHASE

PHASE 10
> fastwalkonce.s(void);
TRANSITION to(11).after(iterations 5);
ENDPHASE

PHASE 11
TRANSITION to(6).after(random .5);
TRANSITION to(12).after(random 1);
ENDPHASE

PHASE 12
> runonce.s(void);
TRANSITION to(13).after(iterations 5);
ENDPHASE

PHASE 13
TRANSITION to(10).after(random .5);
TRANSITION to(12).after(random 1);
ENDPHASE

PHASE 14
> walkinghandstand.s(void);
TRANSITION to(3).after(fallen > .6);
TRANSITION to(0).after(complete);
ENDPHASE

PHASE 15
> skip.s(void);
TRANSITION to(6).after(iterations 2);
ENDPHASE

PHASE 16
> crawl2squat.t(void);
TRANSITION to(1).after(complete);
ENDPHASE


ENDSCRIPT
