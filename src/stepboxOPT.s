
BEGINSCRIPT step(void)

PHASE 0
ACTIONS
	POSE neck2head(-0.0604935326, 300.023132, 30.0117054);
	POSE lTorso2uTorso(-0.0217020195, 599.994812, 29.9336452);
	POSE uTorso2neck(-0.066866681, 299.996765, 30.0130901);
	POSE waist(0.0646896437, 600.034912, 29.9822311);
	POSE rWrist(0.0215347633, 299.964722, 29.9983044);
	POSE lWrist(-0.0149162645, 299.943634, 29.9473152);
	POSE rKnee(0.961317599, 300.00177, 30.0042667);
	POSE rAnkle(-0.198057964, 300.085175, 30.019558);
	POSE lKnee(0.029642377, 299.969635, 30.0666714);
	POSE lAnkle(-0.137673244, 299.980774, 30.0068512);
	POSE rShoulder(0.0972046778, 100.011162, 30.0361767);
	POSE rElbow(-0.0192818828, 100.002525, 30.0030823);
	POSE lShoulder(-0.10089013, 100.013901, 30.0050068);
	POSE lElbow(-0.334629953, 99.9620895, 30.045105);
	POSE rHip(-0.709500909, 299.959106, 29.9365597);
	POSE lHip(-0.0495880954, 299.966766, 30.0276012);
ENDACTIONS
TRANSITION to(1).after(time 0.38149488);
ENDPHASE

PHASE 1
ACTIONS
	POSE rKnee(0.428533047, 299.992554, 30.0201206);
	POSE rAnkle(-0.22923921, 299.991974, 30.0309982);
	POSE lKnee(0.110082522, 300.043427, 29.9863548);
	POSE lAnkle(-0.0962351337, 299.986877, 29.9750652);
	POSE rShoulder(0.0625318438, 99.9973679, 30.0303955);
	POSE rElbow(0.0111001721, 100.064354, 29.9700203);
	POSE lShoulder(-0.0490706563, 100.007057, 30.0584431);
	POSE lElbow(-0.32108885, 100.021431, 30.0156193);
	POSE rHip(-0.744329214, 299.934052, 30.0033226);
	POSE lHip(0.440483212, 199.988419, 90.0028915);
ENDACTIONS
TRANSITION to(-1).after(contact rFoot);
ENDPHASE

ENDSCRIPT
