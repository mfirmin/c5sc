
SCRIPTS step.t, balancecop.t, walk.s, runOPT.s;

BEGINSCRIPT fwdhandspring(void)

PHASE 0
> step.t(void);
TRANSITION to(1).after(complete);
ENDPHASE

PHASE 1
ACTIONS
	POSE rShoulder(-1.72509384, 150.008545, 29.9846859);
	POSE lShoulder(-1.67087567, 150.009247, 29.9987602);
	POSE lKnee(0.0439259112, 299.985229, 29.9673958);
	POSE rKnee(0.455347806, 299.987274, 29.9788475);
	POSE lHip(0.33866331, 199.978104, 30.0079365);
	POSE rHip(-1.0144825, 200.014496, 29.9718876);
	POSE rAnkle(-0.0274237283, 300.004059, 29.9647293);
	POSE lAnkle(0.385014564, 300.006989, 30.0271244);
	POSE rElbow(-0.490332633, 300.01239, 30.0097485);
	POSE lElbow(-0.526136339, 299.98114, 29.9815235);
ENDACTIONS
TRANSITION to(2).after(time 0.505297184);
ENDPHASE

PHASE 2
ACTIONS
	POSE waist(0.305001527, 300.02243, 30.0008507);
	POSE lTorso2uTorso(0.347868979, 299.998657, 30.0399609);
	POSE rShoulder(-1.79815543, 299.996277, 29.9915409);
	POSE lShoulder(-1.77456939, 300.012482, 30.0488377);
	POSE rWrist(-1.50431108, 299.962769, 29.9960136);
	POSE lWrist(-1.49325395, 300.029694, 29.9424152);
	POSE lKnee(0.0737114027, 500.030273, 30.0128193);
	POSE rKnee(0.296325803, 299.990601, 30.0028419);
	POSE rHip(-1.17755902, 200.001877, 29.9830914);
	POSE lHip(0.289818317, 200.003616, 30.0281601);
	POSE rAnkle(0.207763255, 300.002289, 30.0227375);
	POSE lAnkle(0.421081096, 299.978119, 30.0304298);
	POSE rElbow(-0.201228991, 300.033936, 30.0014496);
	POSE lElbow(-0.196571991, 299.998779, 29.9744759);
ENDACTIONS
TRANSITION to(3).after(time 0.175338998);
ENDPHASE

PHASE 3
ACTIONS
	POSE rShoulder(-2.27775049, 299.980377, 30.0181694);
	POSE lShoulder(-2.26379609, 300.015198, 29.9975224);
	POSE rWrist(-1.02400649, 300.008423, 29.9922333);
	POSE lWrist(-0.99472487, 299.996368, 30.0025883);
	POSE rHip(-1.49191976, 300.018219, 30.0430756);
	POSE lHip(0.324510664, 300.004059, 30.0048332);
	POSE rAnkle(0.764715254, 299.978668, 29.9605732);
ENDACTIONS
TRANSITION to(4).after(contact lHand);
ENDPHASE

PHASE 4
ACTIONS
	POSE rShoulder(-2.53397346, 500.019501, 29.9979229);
	POSE lShoulder(-2.52276278, 500.012878, 30.0095196);
	POSE rElbow(-0.474634171, 300.018372, 30.0106297);
	POSE lElbow(-0.52147305, 300.012726, 29.9935265);
	POSE rWrist(-1.54080033, 299.975983, 30.0240097);
	POSE lWrist(-1.56030619, 300.049713, 30.007412);
	POSE rHip(-1.65019596, 299.95993, 30.0044651);
	POSE lHip(1.62197793, 300.020264, 199.984772);
	POSE rKnee(-0.00960143004, 300.039185, 29.9767685);
	POSE lKnee(-0.00826493651, 299.994415, 29.956831);
	POSE rAnkle(0.419130564, 299.978607, 29.9877167);
	POSE lAnkle(-0.0248284582, 300.028748, 29.9514637);
ENDACTIONS
TRANSITION to(5).after(time 0.331096768);
ENDPHASE

PHASE 5
ACTIONS
	POSE waist(-0.217129156, 299.96048, 99.9667206);
	POSE lTorso2uTorso(-0.203641087, 300.011444, 99.9801102);
	POSE rShoulder(-2.49426866, 300.013123, 30.0405579);
	POSE lShoulder(-2.48591828, 299.993378, 30.061842);
	POSE rElbow(-0.83915329, 299.98233, 30.0004845);
	POSE lElbow(-0.807461202, 299.968536, 29.9875183);
	POSE rWrist(-1.67083406, 300.036591, 29.9785023);
	POSE lWrist(-1.68373203, 300.028442, 30.0321064);
	POSE rAnkle(0.216721147, 299.958252, 29.9706268);
	POSE lAnkle(0.225431949, 300.019409, 30.0172424);
	POSE rKnee(0.515468419, 300.012604, 29.999506);
	POSE lKnee(0.476372957, 300.044006, 30.0130787);
	POSE rHip(-1.39543438, 299.96637, 29.994791);
	POSE lHip(2.26460934, 299.981506, 199.983887);
ENDACTIONS
TRANSITION to(6).after(time 0.360729367);
ENDPHASE

PHASE 6
ACTIONS
	POSE rHip(-0.328547686, 299.985535, 30.0195484);
	POSE lHip(2.03902674, 999.989868, 100.038307);
	POSE rKnee(0.374905229, 300.013214, 30.0180969);
	POSE lKnee(1.37675416, 300.04538, 30.0365601);
	POSE waist(-0.368624002, 299.977142, 29.9889889);
	POSE lTorso2uTorso(-0.467514008, 300.006409, 30.0280571);
	POSE rShoulder(-2.72545266, 299.989532, 29.9899788);
	POSE lShoulder(-2.72556472, 299.969818, 30.0195351);
	POSE rAnkle(0.410594076, 299.982483, 30.0376453);
	POSE lAnkle(-0.799212873, 300.019501, 30.022789);
ENDACTIONS
TRANSITION to(7).after(contact lFoot);
ENDPHASE

PHASE 7
ACTIONS
	POSE waist(-0.0933557674, 599.95105, 60.0299149);
	POSE lTorso2uTorso(-0.0199063104, 599.962463, 59.973999);
	POSE rKnee(1.36132193, 300.032898, 30.0095005);
	POSE lKnee(0.285490215, 299.991852, 29.9979);
	POSE rHip(-0.138275847, 299.994537, 29.9985924);
	POSE lHip(0.180724904, 299.993042, 29.979805);
	POSE rAnkle(-0.133742496, 300.000977, 29.9923935);
	POSE lAnkle(-0.605312347, 300.018555, 29.9510345);
	POSE rShoulder(0.0151366843, 100.007294, 29.9785786);
	POSE lShoulder(-0.00897625275, 99.9989777, 29.9447479);
	POSE rElbow(0.0268009659, 300.040924, 30.0290394);
	POSE lElbow(0.0119854333, 300.020233, 30.0385895);
	POSE rWrist(0.00740555767, 299.973572, 29.9580898);
	POSE lWrist(-0.0135270944, 300.012878, 29.991787);
ENDACTIONS
TRANSITION to(8).after(time 0.981863081);
ENDPHASE

PHASE 8
> runOPT.s(void);
TRANSITION to(-1).after(complete);
ENDPHASE

ENDSCRIPT