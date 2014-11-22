
SCRIPTS step.t, balancecop.t, walk.s, walk2times.s, stepboxOPT.s;

BEGINSCRIPT fwdhandspring(void)

PHASE 0
> stepboxOPT.s(void);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
	POSE rShoulder(-1.67227387, 149.993317, 29.8784256);
	POSE lShoulder(-1.68547738, 149.999527, 29.9621658);
	POSE lKnee(0.058276251, 299.981537, 29.9535961);
	POSE rKnee(0.512715161, 300.033386, 30.0027027);
	POSE lHip(0.322153032, 200.001373, 30.0087376);
	POSE rHip(-0.950896323, 199.969681, 29.9301071);
	POSE rAnkle(-0.0150394579, 300.006104, 30.0322247);
	POSE lAnkle(0.404958725, 299.96283, 29.9893036);
	POSE rElbow(-0.529260814, 300.015778, 29.9536724);
	POSE lElbow(-0.542360783, 300.022827, 30.0557098);
ENDACTIONS
TRANSITION to(2).after(time 0.52758503);
ENDPHASE

PHASE 2
ACTIONS
	POSE waist(0.278013468, 300.017853, 30.0387783);
	POSE lTorso2uTorso(0.313446999, 299.930084, 29.9976368);
	POSE rShoulder(-1.73480344, 300.010254, 30.055479);
	POSE lShoulder(-1.84994328, 300.035187, 29.9936008);
	POSE rWrist(-1.56666279, 300.000488, 30.0020275);
	POSE lWrist(-1.53773439, 299.968323, 29.9587803);
	POSE lKnee(0.0661283955, 499.949371, 30.0362797);
	POSE rKnee(0.322279662, 299.99649, 29.9982491);
	POSE rHip(-1.13944292, 199.967499, 29.9674778);
	POSE lHip(0.30270797, 199.933701, 30.062376);
	POSE rAnkle(0.253528297, 300.007843, 29.923624);
	POSE lAnkle(0.411020935, 299.97702, 29.992857);
	POSE rElbow(-0.146148354, 299.984924, 30.0312424);
	POSE lElbow(-0.231032386, 299.989105, 29.9775772);
ENDACTIONS
TRANSITION to(3).after(time 0.296385527);
ENDPHASE

PHASE 3
ACTIONS
	POSE rShoulder(-2.28047657, 300.016937, 29.9657154);
	POSE lShoulder(-2.31191444, 299.984528, 30.0249443);
	POSE rWrist(-1.1121552, 300.011047, 29.9489632);
	POSE lWrist(-1.02660489, 299.951782, 29.9531689);
	POSE rHip(-1.47735155, 300.016113, 30.0634136);
	POSE lHip(0.253416657, 300.041962, 30.0157394);
	POSE rAnkle(0.81892848, 300.017151, 29.9707718);
ENDACTIONS
TRANSITION to(4).after(contact lHand);
ENDPHASE

PHASE 4
ACTIONS
	POSE rShoulder(-2.51126957, 500.023438, 30.0520096);
	POSE lShoulder(-2.46378851, 500.047424, 30.0371132);
	POSE rElbow(-0.499471545, 299.997498, 29.9859524);
	POSE lElbow(-0.518277168, 300.030975, 30.038269);
	POSE rWrist(-1.47816455, 300.055145, 30.0479774);
	POSE lWrist(-1.49793518, 299.971649, 29.9582424);
	POSE rHip(-1.59368515, 299.993317, 29.9970169);
	POSE lHip(1.599792, 300.037292, 199.92038);
	POSE rKnee(0.00194050558, 299.991638, 30.0102081);
	POSE lKnee(0.0779946595, 299.951508, 29.9784889);
	POSE rAnkle(0.452118546, 299.995453, 29.9378853);
	POSE lAnkle(0.0313960351, 300.055511, 30.0727921);
ENDACTIONS
TRANSITION to(5).after(time 0.357590497);
ENDPHASE

PHASE 5
ACTIONS
	POSE waist(-0.200000003, 300, 100);
	POSE lTorso2uTorso(-0.200000003, 300, 100);
	POSE rShoulder(-2.5, 300, 30);
	POSE lShoulder(-2.5, 300, 30);
	POSE rElbow(-0.800000012, 300, 30);
	POSE lElbow(-0.800000012, 300, 30);
	POSE rWrist(-1.70000005, 300, 30);
	POSE lWrist(-1.70000005, 300, 30);
	POSE rAnkle(0.200000003, 300, 30);
	POSE lAnkle(0.200000003, 300, 30);
	POSE rKnee(0.5, 300, 30);
	POSE lKnee(0.5, 300, 30);
	POSE rHip(-1.39999998, 300, 30);
	POSE lHip(2.29999995, 300, 200);
ENDACTIONS
TRANSITION to(6).after(time 0.400000006);
ENDPHASE

PHASE 6
ACTIONS
	POSE rHip(-0.300000012, 300, 30);
	POSE lHip(2, 1000, 100);
	POSE rKnee(0.400000006, 300, 30);
	POSE lKnee(1.39999998, 300, 30);
	POSE waist(-0.400000006, 300, 30);
	POSE lTorso2uTorso(-0.400000006, 300, 30);
	POSE rShoulder(-2.70000005, 300, 30);
	POSE lShoulder(-2.70000005, 300, 30);
	POSE rAnkle(0.400000006, 300, 30);
	POSE lAnkle(-0.800000012, 300, 30);
ENDACTIONS
TRANSITION to(7).after(contact lFoot);
ENDPHASE

PHASE 7
ACTIONS
	POSE waist(-0.100000001, 600, 60);
	POSE lTorso2uTorso(0, 600, 60);
	POSE rKnee(1.29999995, 300, 30);
	POSE lKnee(0.300000012, 300, 30);
	POSE rHip(-0.100000001, 300, 30);
	POSE lHip(0.200000003, 300, 30);
	POSE rAnkle(-0, 300, 30);
	POSE lAnkle(-0.699999988, 300, 30);
	POSE rShoulder(0, 100, 30);
	POSE lShoulder(0, 100, 30);
	POSE rElbow(0, 300, 30);
	POSE lElbow(0, 300, 30);
	POSE rWrist(0, 300, 30);
	POSE lWrist(0, 300, 30);
ENDACTIONS
TRANSITION to(8).after(time 1);
ENDPHASE

PHASE 8
> walk2times.s(void);
TRANSITION to(9).after(complete);
ENDPHASE

PHASE 9
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT