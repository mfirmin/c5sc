SCRIPTS simbiconslowonce.t;

BEGINSCRIPT walk(goal, iters)
PHASE 0
#                   (dt, cde, cdo,  cve, cvo,  tor, swhe, swho, swke, swko, stke, stko, ankle)
 > simbiconslowonce.t(linterp(goal, 0.3, 1.3, 0.6, 0.3), 0.0, linterp(goal,0.3,1.3,-1.2,-2.2), linterp(goal,0.3,1.3,-.1,-.2), 0.0, 0.0, linterp(goal,0.3,1.3,-.7,-.4), linterp(goal,0.3,1.3,.4,.7), linterp(goal,0.3,1.3,0.8,1.1), .05, 0.05, 0.1, linterp(goal,0.3,1.3,-.1,-.2), 300., linterp(goal,0.3,1.3,120.,30.));
TRANSITION to(-1).after(iterations iters);
ENDPHASE

ENDSCRIPT
