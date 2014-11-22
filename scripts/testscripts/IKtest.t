SCRIPTS balance2ankle.t;


BEGINSCRIPT IKtest(void)

PHASE 0
> balance2ankle.t(2);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
   	IK rHand.targetglobal(.4, 1.75, -10).base(rShoulder);
	IK lHand.targetglobal(-.1, .9, -10).base(lShoulder);
ENDACTIONS
TRANSITION to(2).after(time 2);
ENDPHASE

PHASE 2
ACTIONS
	IK rHand.targetlocal(.4, .4, 0).base(rShoulder);
	IK lHand.targetlocal(-.4,-.4,0).base(lShoulder);
ENDACTIONS
TRANSITION to(-1).after(time 500);
ENDPHASE

ENDSCRIPT
