using namespace OGG;

//Ogg快捷函数
bool KoishiAudioTool::OGG::OGGeasyDecode(const str &fileName, stream &pcmOut, volatile double &complete) {
	OGGobject oo;
	oo.loadFile(fileName);
	oo.initDecoder();
	oo.initPCM();
	complete = 0;
	int i = 3;
	int j = 0;
	while(oo.packDecode(i++)) {
		oo.makePCM(j++);
		complete = 100.f * j / oo.blocks.size();
	}
	oo.makePCMstream(pcmOut);
	return pcmOut.length > 0;
}
bool KoishiAudioTool::OGG::OGGeasyDecodeAndPlay(const str &fileName) {
	OGGobject oo;
	oo.loadFile(fileName);
	oo.initDecoder();
	oo.initPCM();
	int i = 3;
	int j = 0;
	while(oo.packDecode(i++)) {
		oo.makePCM(j++);
	}
	stream pcmOut;
	oo.makePCMstream(pcmOut);
	PCMdevice pd;
	pd.initFormat(oo.info.channels, 16, oo.info.sampleRate, oo.info.bitrateNorm, 2 * oo.info.channels, 0);
	pd.play(pcmOut);
	return pcmOut.length > 0;
}
////////////////////////////////////////////////////////////////////////////
//ogg编解码
////////////////////////////////////////////////////////////////////////////
inline double KoishiAudioTool::OGG::OGGsupport::bit32ToFloat(dword d) {
	double M = d & 0x001FFFFF;
	long S = d & 0x80000000;
	long E = (d & 0x7FE00000) >> 21;
	return ldexp(S ? M : -M, E - 788);
}
inline int KoishiAudioTool::OGG::OGGsupport::MapType1_Quantvals(int dimension, int entryCount) {
	//1类映射参数估计
	int vals;
	if(entryCount<1)
		return 0;
	vals = floor(pow((float)entryCount, 1.f / dimension));
	if(vals < 1)
		vals = 1;
	while(1) {
		long acc = 1;
		long acc1 = 1;
		int i;
		for(i = 0; i < dimension; i++) {
			if(entryCount / vals < acc)
				break;
			acc *= vals;
			if(LONG_MAX / (vals + 1) < acc1) {
				acc1 = LONG_MAX;
			} else {
				acc1 *= vals + 1;
			}
		}
		if(i >= dimension && acc <= entryCount && acc1 > entryCount) {
			return vals;
		} else {
			if(i < dimension || acc > entryCount) {
				vals--;
			} else {
				vals++;
			}
		}
	}
}
inline int KoishiAudioTool::OGG::OGGsupport::ilog(int n) {
	//类似于对数取整加1 0,1,2,3,4,5,6,7,8 → 0,1,1,2,2,3,3,3,4
	int result = 0;
	while(n > 0) {
		n /= 2;
		result++;
	}
	return result;
}
inline int KoishiAudioTool::OGG::OGGsupport::lowNeighbor(queue list, int n) {
	//在数列的前n项中寻找对应的下标，使得其值在所有比list[n]小中的值里是最大的。返回-1则寻找失败(比如n=0一定会失败
	if(n < 0)
		n = 0;
	if(n >= list.size())
		n = list.size() - 1;
	int topValue = list[n];
	int maxID = -1;
	int maxValue = -1;
	for(int i = 0; i<n; i++) {
		int value = list[i];
		if(value >= topValue)
			continue;
		if(value > maxValue) {
			maxID = i;
			maxValue = value;
		}
	}
	return maxID;
}
inline int KoishiAudioTool::OGG::OGGsupport::highNeighbor(queue list, int n) {
	//在数列的前n项中寻找对应的下标，使得其值在所有比list[n]大中的值里是最小的。
	if(n < 0)
		n = 0;
	if(n >= list.size())
		n = list.size() - 1;
	int bottomValue = list[n];
	int minID = -1;
	int minValue = LONG_MAX;
	for(int i = 0; i<n; i++) {
		int value = list[i];
		if(value <= bottomValue)
			continue;
		if(value < minValue) {
			minID = i;
			minValue = value;
		}
	}
	return minID;
}
inline int KoishiAudioTool::OGG::OGGsupport::renderPoint(int x0, int y0, int x1, int y1, int X) {
	int dy = y1 - y0;
	int adx = x1 - x0;
	int ady = abs(dy);
	int err = ady * (X - x0);
	int off = err / adx;
	return dy > 0 ? (y0 + off) : (y0 - off);
}
inline void KoishiAudioTool::OGG::OGGsupport::renderLine(int x0, int y0, int x1, int y1, queue &v) {
	while(v.size()<x1)
		v.push_back(0);
	int dy = y1 - y0;
	int adx = x1 - x0;
	int ady = abs(dy);
	int base = dy / adx;
	int x = x0;
	int y = y0;
	int err = 0;
	int sy = dy < 0 ? (base - 1) : (base + 1);
	ady -= abs(base) * adx;
	v[x] = y;
	for(x = x0 + 1; x <= x1 - 1; x++) {
		err += ady;
		if(err >= adx) {
			err -= adx;
			y += sy;
		} else {
			y += base;
		}
		v[x] = y;
	}
}
inline void KoishiAudioTool::OGG::OGGsupport::renderLine(int x0, int y0, int x1, int y1, sequence &vf) {
	while(vf.size()<x1)
		vf.push_back(0);
	int dy = y1 - y0;
	int adx = x1 - x0;
	int ady = abs(dy);
	int base = dy / adx;
	int x = x0;
	int y = y0;
	int err = 0;
	int sy = dy < 0 ? (base - 1) : (base + 1);
	ady -= abs(base) * adx;
	vf[x] *= invDb(y);
	for(x = x0 + 1; x <= x1 - 1; x++) {
		err += ady;
		if(err >= adx) {
			err -= adx;
			y += sy;
		} else {
			y += base;
		}
		vf[x] *= invDb(y);
	}
}
inline double KoishiAudioTool::OGG::OGGsupport::invDb(long p) {
	if(p<0)
		p = 0;
	if(p>255)
		p = 255;
	double TABLE[256] = {
		1.0649863e-07, 1.1341951e-07, 1.2079015e-07, 1.2863978e-07, 1.3699951e-07, 1.4590251e-07, 1.5538408e-07, 1.6548181e-07,
		1.7623575e-07, 1.8768855e-07, 1.9988561e-07, 2.128753e-07, 2.2670913e-07, 2.4144197e-07, 2.5713223e-07, 2.7384213e-07,
		2.9163793e-07, 3.1059021e-07, 3.3077411e-07, 3.5226968e-07, 3.7516214e-07, 3.9954229e-07, 4.2550680e-07, 4.5315863e-07,
		4.8260743e-07, 5.1396998e-07, 5.4737065e-07, 5.8294187e-07, 6.2082472e-07, 6.6116941e-07, 7.0413592e-07, 7.4989464e-07,
		7.9862701e-07, 8.5052630e-07, 9.0579828e-07, 9.6466216e-07, 1.0273513e-06, 1.0941144e-06, 1.1652161e-06, 1.2409384e-06,
		1.3215816e-06, 1.4074654e-06, 1.4989305e-06, 1.5963394e-06, 1.7000785e-06, 1.8105592e-06, 1.9282195e-06, 2.0535261e-06,
		2.1869758e-06, 2.3290978e-06, 2.4804557e-06, 2.6416497e-06, 2.8133190e-06, 2.9961443e-06, 3.1908506e-06, 3.3982101e-06,
		3.6190449e-06, 3.8542308e-06, 4.1047004e-06, 4.3714470e-06, 4.6555282e-06, 4.9580707e-06, 5.2802740e-06, 5.6234160e-06,
		5.9888572e-06, 6.3780469e-06, 6.7925283e-06, 7.2339451e-06, 7.7040476e-06, 8.2047000e-06, 8.7378876e-06, 9.3057248e-06,
		9.9104632e-06, 1.0554501e-05, 1.1240392e-05, 1.1970856e-05, 1.2748789e-05, 1.3577278e-05, 1.4459606e-05, 1.5399272e-05,
		1.6400004e-05, 1.7465768e-05, 1.8600792e-05, 1.9809576e-05, 2.1096914e-05, 2.2467911e-05, 2.3928002e-05, 2.5482978e-05,
		2.7139006e-05, 2.8902651e-05, 3.0780908e-05, 3.2781225e-05, 3.4911534e-05, 3.7180282e-05, 3.9596466e-05, 4.2169667e-05,
		4.4910090e-05, 4.7828601e-05, 5.0936773e-05, 5.4246931e-05, 5.7772202e-05, 6.1526565e-05, 6.5524908e-05, 6.9783085e-05,
		7.4317983e-05, 7.9147585e-05, 8.4291040e-05, 8.9768747e-05, 9.5602426e-05, 0.00010181521, 0.00010843174, 0.00011547824,
		0.00012298267, 0.00013097477, 0.00013948625, 0.00014855085, 0.00015820453, 0.00016848555, 0.00017943469, 0.00019109536,
		0.00020351382, 0.00021673929, 0.00023082423, 0.00024582449, 0.00026179955, 0.00027881276, 0.00029693158, 0.00031622787,
		0.00033677814, 0.00035866388, 0.00038197188, 0.00040679456, 0.00043323036, 0.00046138411, 0.00049136745, 0.00052329927,
		0.00055730621, 0.00059352311, 0.00063209358, 0.00067317058, 0.00071691700, 0.00076350630, 0.00081312324, 0.00086596457,
		0.00092223983, 0.00098217216, 0.0010459992, 0.0011139742, 0.0011863665, 0.0012634633, 0.0013455702, 0.0014330129,
		0.0015261382, 0.0016253153, 0.0017309374, 0.0018434235, 0.0019632195, 0.0020908006, 0.0022266726, 0.0023713743,
		0.0025254795, 0.0026895994, 0.0028643847, 0.0030505286, 0.0032487691, 0.0034598925, 0.0036847358, 0.0039241906,
		0.0041792066, 0.0044507950, 0.0047400328, 0.0050480668, 0.0053761186, 0.0057254891, 0.0060975636, 0.0064938176,
		0.0069158225, 0.0073652516, 0.0078438871, 0.0083536271, 0.0088964928, 0.009474637, 0.010090352, 0.010746080,
		0.011444421, 0.012188144, 0.012980198, 0.013823725, 0.014722068, 0.015678791, 0.016697687, 0.017782797,
		0.018938423, 0.020169149, 0.021479854, 0.022875735, 0.024362330, 0.025945531, 0.027631618, 0.029427276,
		0.031339626, 0.033376252, 0.035545228, 0.037855157, 0.040315199, 0.042935108, 0.045725273, 0.048696758,
		0.051861348, 0.055231591, 0.058820850, 0.062643361, 0.066714279, 0.071049749, 0.075666962, 0.080584227,
		0.085821044, 0.091398179, 0.097337747, 0.10366330, 0.11039993, 0.11757434, 0.12521498, 0.13335215,
		0.14201813, 0.15124727, 0.16107617, 0.17154380, 0.18269168, 0.19456402, 0.20720788, 0.22067342,
		0.23501402, 0.25028656, 0.26655159, 0.28387361, 0.30232132, 0.32196786, 0.34289114, 0.36517414,
		0.38890521, 0.41417847, 0.44109412, 0.46975890, 0.50028648, 0.53279791, 0.56742212, 0.60429640,
		0.64356699, 0.68538959, 0.72993007, 0.77736504, 0.82788260, 0.88168307, 0.9389798, 1
	};
	return TABLE[p];
}
inline queue KoishiAudioTool::OGG::OGGsupport::qSort(const queue &list) {
	queue q;
	for(int j = 0; j<list.size(); j++)
		q.push_back(0);
	for(int j = 1; j<list.size(); j++)
		for(int k = 0; k<j; k++)
			q[list[j] >= list[k] ? j : k]++;
	return q;
}
inline queue KoishiAudioTool::OGG::OGGsupport::qResort(const queue &list, const queue &indexList) {
	queue sorted = list;
	for(int j = 0; j<sorted.size(); j++)
		sorted[indexList[j]] = list[j];
	return sorted;
}
///////////////////////////////
double KoishiAudioTool::OGG::MDCT::PI = 3.1415926536f;
double KoishiAudioTool::OGG::MDCT::cosPI_8(int k) {
	if(k < 0)
		k = -k;
	if(k == 0)
		return 1;
	if(k == 1)
		return .92387953251128675613F;
	if(k == 2)
		return .70710678118654752441F;
	if(k == 3)
		return .38268343236508977175F;
	if(k == 4)
		return 0;
	if(k <= 8)
		return -cosPI_8(8 - k);
	if(k <= 16)
		return -cosPI_8(k - 8);
	return cosPI_8(k % 16);
}
void KoishiAudioTool::OGG::MDCT::initial(int n0) {
	n = n0;
	log2n = (int)floor(0.5 + log((double)n0) / log(2.0));
	bitRev = new int[n / 4];
	memset(bitRev, 0, sizeof(int)*(n / 4));
	trig = new double[n + n / 4];
	memset(trig, 0, sizeof(double)*(n + n / 4));
	for(int i = 0; i<n / 4; i++) {
		trig[2 * i] = cos((PI / n)*(4 * i));
		trig[2 * i + 1] = -sin(((PI) / n)*(4 * i));
		trig[2 * i + n / 2] = cos(PI / (2 * n)*(2 * i + 1));
		trig[2 * i + n / 2 + 1] = sin(PI / (2 * n)*(2 * i + 1));
	}
	for(int i = 0; i<n / 8; i++) {
		trig[2 * i + n] = cos(PI / n*(4 * i + 2))*0.5;
		trig[2 * i + n + 1] = -sin(PI / n*(4 * i + 2))*0.5;
	}
	int mask = (1 << (log2n - 1)) - 1;
	int msb = 1 << (log2n - 2);
	for(int i = 0; i<n / 8; i++) {
		int acc = 0;
		for(int j = 0; msb >> j; j++) {
			if(i & (msb >> j))
				acc |= 1 << j;
			bitRev[2 * i] = (mask & ~acc) - 1;
			bitRev[2 * i + 1] = acc;
		}
	}
	scale = 4.0 / n;
}
void KoishiAudioTool::OGG::MDCT::destory() {
	delete[] bitRev;
	delete[] trig;
}
void KoishiAudioTool::OGG::MDCT::butterfly8(double *x) {
	register double r0, r1, r2, r3;
	r0 = x[6] + x[2];
	r1 = x[6] - x[2];
	r2 = x[4] + x[0];
	r3 = x[4] - x[0];
	x[6] = r0 + r2;
	x[4] = r0 - r2;
	r0 = x[5] - x[1];
	r2 = x[7] - x[3];
	x[0] = r1 + r0;
	x[2] = r1 - r0;
	r0 = x[5] + x[1];
	r1 = x[7] + x[3];
	x[3] = r2 + r3;
	x[1] = r2 - r3;
	x[7] = r1 + r0;
	x[5] = r1 - r0;
}
void KoishiAudioTool::OGG::MDCT::butterfly16(double *x) {
	register double r0, r1;
	r0 = x[1] - x[9];
	r1 = x[0] - x[8];
	x[8] += x[0];
	x[9] += x[1];
	x[0] = (r0 + r1) * cosPI_8(2);
	x[1] = (r0 - r1) * cosPI_8(2);
	r0 = x[3] - x[11];
	r1 = x[10] - x[2];
	x[10] += x[2];
	x[11] += x[3];
	x[2] = r0;
	x[3] = r1;
	r0 = x[12] - x[4];
	r1 = x[13] - x[5];
	x[12] += x[4];
	x[13] += x[5];
	x[4] = (r0 - r1) * cosPI_8(2);
	x[5] = (r0 + r1) * cosPI_8(2);
	r0 = x[14] - x[6];
	r1 = x[15] - x[7];
	x[14] += x[6];
	x[15] += x[7];
	x[6] = r0;
	x[7] = r1;
	butterfly8(x);
	butterfly8(x + 8);
}
void KoishiAudioTool::OGG::MDCT::butterfly32(double *x) {
	register double r0, r1;
	r0 = x[30] - x[14];
	r1 = x[31] - x[15];
	x[30] += x[14];
	x[31] += x[15];
	x[14] = r0;
	x[15] = r1;
	r0 = x[28] - x[12];
	r1 = x[29] - x[13];
	x[28] += x[12];
	x[29] += x[13];
	x[12] = r0 * cosPI_8(1) - r1 * cosPI_8(3);
	x[13] = r0 * cosPI_8(3) + r1 * cosPI_8(1);
	r0 = x[26] - x[10];
	r1 = x[27] - x[11];
	x[26] += x[10];
	x[27] += x[11];
	x[10] = (r0 - r1)*cosPI_8(2);
	x[11] = (r0 + r1)*cosPI_8(2);
	r0 = x[24] - x[8];
	r1 = x[25] - x[9];
	x[24] += x[8];
	x[25] += x[9];
	x[8] = r0 * cosPI_8(3) - r1 * cosPI_8(1);
	x[9] = r1 * cosPI_8(3) + r0 * cosPI_8(1);
	r0 = x[22] - x[6];
	r1 = x[7] - x[23];
	x[22] += x[6];
	x[23] += x[7];
	x[6] = r1;
	x[7] = r0;
	r0 = x[4] - x[20];
	r1 = x[5] - x[21];
	x[20] += x[4];
	x[21] += x[5];
	x[4] = r1 * cosPI_8(1) + r0 * cosPI_8(3);
	x[5] = r1 * cosPI_8(3) - r0 * cosPI_8(1);
	r0 = x[2] - x[18];
	r1 = x[3] - x[19];
	x[18] += x[2];
	x[19] += x[3];
	x[2] = (r1 + r0)*cosPI_8(2);
	x[3] = (r1 - r0)*cosPI_8(2);
	r0 = x[0] - x[16];
	r1 = x[1] - x[17];
	x[16] += x[0];
	x[17] += x[1];
	x[0] = r1 * cosPI_8(3) + r0 * cosPI_8(1);
	x[1] = r1 * cosPI_8(1) - r0 * cosPI_8(3);
	butterfly16(x);
	butterfly16(x + 16);
}
void KoishiAudioTool::OGG::MDCT::butterflyFirst(double *T, double *x, int points) {
	double *x1 = x + points - 8;
	double *x2 = x + points / 2 - 8;
	register double r0, r1;
	do {
		r0 = x1[6] - x2[6];
		r1 = x1[7] - x2[7];
		x1[6] += x2[6];
		x1[7] += x2[7];
		x2[6] = r1 * T[1] + r0 * T[0];
		x2[7] = r1 * T[0] - r0 * T[1];
		r0 = x1[4] - x2[4];
		r1 = x1[5] - x2[5];
		x1[4] += x2[4];
		x1[5] += x2[5];
		x2[4] = r1 * T[5] + r0 * T[4];
		x2[5] = r1 * T[4] - r0 * T[5];
		r0 = x1[2] - x2[2];
		r1 = x1[3] - x2[3];
		x1[2] += x2[2];
		x1[3] += x2[3];
		x2[2] = r1 * T[9] + r0 * T[8];
		x2[3] = r1 * T[8] - r0 * T[9];
		r0 = x1[0] - x2[0];
		r1 = x1[1] - x2[1];
		x1[0] += x2[0];
		x1[1] += x2[1];
		x2[0] = r1 * T[13] + r0 * T[12];
		x2[1] = r1 * T[12] - r0 * T[13];
		x1 -= 8;
		x2 -= 8;
		T += 16;
	} while(x2 >= x);
}
void KoishiAudioTool::OGG::MDCT::butterflyGeneric(double *T, double *x, int points, int trigint) {
	double *x1 = x + points - 8;
	double *x2 = x + points / 2 - 8;
	register double r0, r1;
	do {
		r0 = x1[6] - x2[6];
		r1 = x1[7] - x2[7];
		x1[6] += x2[6];
		x1[7] += x2[7];
		x2[6] = r1 * T[1] + r0 * T[0];
		x2[7] = r1 * T[0] - r0 * T[1];
		T += trigint;
		r0 = x1[4] - x2[4];
		r1 = x1[5] - x2[5];
		x1[4] += x2[4];
		x1[5] += x2[5];
		x2[4] = r1 * T[1] + r0 * T[0];
		x2[5] = r1 * T[0] - r0 * T[1];
		T += trigint;
		r0 = x1[2] - x2[2];
		r1 = x1[3] - x2[3];
		x1[2] += x2[2];
		x1[3] += x2[3];
		x2[2] = r1 * T[1] + r0 * T[0];
		x2[3] = r1 * T[0] - r0 * T[1];
		T += trigint;
		r0 = x1[0] - x2[0];
		r1 = x1[1] - x2[1];
		x1[0] += x2[0];
		x1[1] += x2[1];
		x2[0] = r1 * T[1] + r0 * T[0];
		x2[1] = r1 * T[0] - r0 * T[1];
		T += trigint;
		x1 -= 8;
		x2 -= 8;
	} while(x2 >= x);
}
void KoishiAudioTool::OGG::MDCT::butterfly(double *x, int points) {
	int stages = log2n - 5;
	if(--stages > 0)
		butterflyFirst(trig, x, points);
	for(int i = 1; --stages>0; i++)
		for(int j = 0; j<(1 << i); j++)
			butterflyGeneric(trig, x + (points >> i) * j, points >> i, 4 << i);
	for(int i = 0; i<points; i += 32)
		butterfly32(x + i);
}
void KoishiAudioTool::OGG::MDCT::bitReverse(double *x) {
	double *w0 = x;
	double *w1 = x = w0 + (n >> 1);
	double *T = trig + n;
	int *bit = bitRev;
	do {
		double *x0 = x + bit[0];
		double *x1 = x + bit[1];
		register double r0, r1, r2, r3;
		r0 = x0[1] - x1[1];
		r1 = x0[0] + x1[0];
		r2 = r1 * T[0] + r0 * T[1];
		r3 = r1 * T[1] - r0 * T[0];
		w1 -= 4;
		r0 = 0.5*(x0[1] + x1[1]);
		r1 = 0.5*(x0[0] - x1[0]);
		w0[0] = r0 + r2;
		w1[2] = r0 - r2;
		w0[1] = r3 + r1;
		w1[3] = r3 - r1;
		x0 = x + bit[2];
		x1 = x + bit[3];
		r0 = x0[1] - x1[1];
		r1 = x0[0] + x1[0];
		r2 = r1 * T[2] + r0 * T[3];
		r3 = r1 * T[3] - r0 * T[2];
		r0 = 0.5*(x0[1] + x1[1]);
		r1 = 0.5*(x0[0] - x1[0]);
		w0[2] = r0 + r2;
		w1[0] = r0 - r2;
		w0[3] = r1 + r3;
		w1[1] = r3 - r1;
		T += 4;
		bit += 4;
		w0 += 4;
	} while(w0 < w1);
}
void KoishiAudioTool::OGG::MDCT::backward(double *in, double *out) {
	int n2 = n / 2;
	int n4 = n / 4;
	double *iX = in + n2 - 7;
	double *oX = out + n2 + n4;
	double *T = trig + n4;
	do {
		oX -= 4;
		oX[0] = -iX[2] * T[3] - iX[0] * T[2];
		oX[1] = iX[0] * T[3] - iX[2] * T[2];
		oX[2] = -iX[6] * T[1] - iX[4] * T[0];
		oX[3] = iX[4] * T[1] - iX[6] * T[0];
		iX -= 8;
		T += 4;
	} while(iX >= in);
	iX = in + n2 - 8;
	oX = out + n2 + n4;
	T = trig + n4;
	do {
		T -= 4;
		oX[0] = iX[4] * T[3] + iX[6] * T[2];
		oX[1] = iX[4] * T[2] - iX[6] * T[3];
		oX[2] = iX[0] * T[1] + iX[2] * T[0];
		oX[3] = iX[0] * T[0] - iX[2] * T[1];
		iX -= 8;
		oX += 4;
	} while(iX >= in);
	butterfly(out + n2, n2);
	bitReverse(out);
	double *oX1 = out + n2 + n4;
	double *oX2 = out + n2 + n4;
	iX = out;
	T = trig + n2;
	do {
		oX1 -= 4;
		oX1[3] = iX[0] * T[1] - iX[1] * T[0];
		oX2[0] = -iX[0] * T[0] - iX[1] * T[1];
		oX1[2] = iX[2] * T[3] - iX[3] * T[2];
		oX2[1] = -iX[2] * T[2] - iX[3] * T[3];
		oX1[1] = iX[4] * T[5] - iX[5] * T[4];
		oX2[2] = -iX[4] * T[4] - iX[5] * T[5];
		oX1[0] = iX[6] * T[7] - iX[7] * T[6];
		oX2[3] = -iX[6] * T[6] - iX[7] * T[7];
		oX2 += 4;
		iX += 8;
		T += 8;
	} while(iX < oX1);
	iX = out + n2 + n4;
	oX1 = out + n4;
	oX2 = oX1;
	do {
		oX1 -= 4;
		iX -= 4;
		oX2[0] = -(oX1[3] = iX[3]);
		oX2[1] = -(oX1[2] = iX[2]);
		oX2[2] = -(oX1[1] = iX[1]);
		oX2[3] = -(oX1[0] = iX[0]);
		oX2 += 4;
	} while(oX2 < iX);
	iX = out + n2 + n4;
	oX1 = out + n2 + n4;
	oX2 = out + n2;
	do {
		oX1 -= 4;
		oX1[0] = iX[3];
		oX1[1] = iX[2];
		oX1[2] = iX[1];
		oX1[3] = iX[0];
		iX += 4;
	} while(oX1 > oX2);
}
void KoishiAudioTool::OGG::MDCT::forward(double *in, double *out) {
	int n2 = n / 2;
	int n4 = n / 4;
	int n8 = n / 8;
	double *w = new double[n];
	double *w2 = w + n2;
	register double r0, r1;
	double *x0 = in + n2 + n4;
	double *x1 = x0 + 1;
	double *T = trig + n2;
	int i = 0;
	for(; i<n8; i += 2) {
		x0 -= 4;
		T -= 2;
		r0 = x0[2] + x1[0];
		r1 = x0[0] + x1[2];
		w2[i] = r1*T[1] + r0*T[0];
		w2[i + 1] = r1*T[0] - r0*T[1];
		x1 += 4;
	}
	x1 = in + 1;
	for(; i<n2 - n8; i += 2) {
		x0 -= 4;
		T -= 2;
		r0 = x0[2] - x1[0];
		r1 = x0[0] - x1[2];
		w2[i] = r1*T[1] + r0*T[0];
		w2[i + 1] = r1*T[0] - r0*T[1];
		x1 += 4;
	}
	x0 = in + n;
	for(; i<n2; i += 2) {
		T -= 2;
		x0 -= 4;
		r0 = -x0[2] - x1[0];
		r1 = -x0[0] - x1[2];
		w2[i] = r1*T[1] + r0*T[0];
		w2[i + 1] = r1*T[0] - r0*T[1];
		x1 += 4;
	}
	butterfly(w + n2, n2);
	bitReverse(w);
	T = trig + n2;
	x0 = out + n2;
	for(i = 0; i<n4; i++) {
		x0--;
		out[i] = scale*(w[0] * T[0] + w[1] * T[1]);
		x0[0] = scale*(w[0] * T[1] - w[1] * T[0]);
		w += 2;
		T += 2;
	}
}
///////////////////////////////
OGGpage::OGGpage() {
	uchar ver = 0;
	type = 0;
	sampleTotalCount = 0;
	serial = 0;
	sequence = 0;
	checkCRC = 0;
	segCount = 0;
	segLength.clear();
	segData.clear();
}
VorbisCodeBook::VorbisCodeBook() {
	dimension = 0;
	entryCount = 0;
	ordered = 0;
	sparsed = 0;
	mappingType = NO_LOOK_UP;
}
bool VorbisCodeBook::buildFromData(stream &data) {
	char BCVid[4] = {0};
	data.bitRead(&BCVid, 24);
	if(str(BCVid) == "BCV") {
		data.bitRead(&dimension, 16);
		data.bitRead(&entryCount, 24);
		data.bitRead(&ordered, 1);
		if(!ordered) {
			data.bitRead(&sparsed, 1);
			if(sparsed) {
				for(dword i = 0; i<entryCount; i++) {
					bool flag = 0;
					data.bitRead(&flag, 1);
					if(flag) {
						long num = 0;
						data.bitRead(&num, 5);
						entryLen.push_back(num + 1);
					} else {
						long num = 0;
						entryLen.push_back(0);
					}
				}
			} else {
				for(dword i = 0; i<entryCount; i++) {
					long num = 0;
					data.bitRead(&num, 5);
					entryLen.push_back(num + 1);
				}
			}
		} else {
			long length = 0;
			data.bitRead(&length, 5);
			length++;
			for(dword i = 0; i<entryCount;) {
				long len = OGGsupport::ilog(entryCount - i);
				long num = 0;
				data.bitRead(&num, len);
				for(dword j = 0; j<num; j++, i++) {
					entryLen.push_back(length);
				}
				length++;
			}
		}
		data.bitRead(&mappingType, 4);
		if(mappingType != 0) {
			dword dTemp = 0;
			data.bitRead(&dTemp, 32);
			mappingPara.min = OGGsupport::bit32ToFloat(dTemp);
			dTemp = 0;
			data.bitRead(&dTemp, 32);
			mappingPara.delta = OGGsupport::bit32ToFloat(dTemp);
			data.bitRead(&mappingPara.valueBits, 4);
			mappingPara.valueBits++;
			data.bitRead(&mappingPara.seqP, 1);
			if(mappingType == VorbisCodeBook::LOOK_UP_1) {
				if(dimension == 0) {
					mappingPara.valuesCount = 0;
				} else {
					mappingPara.valuesCount = OGGsupport::MapType1_Quantvals(dimension, entryCount);
				}
			}
			if(mappingType == VorbisCodeBook::LOOK_UP_2) {
				mappingPara.valuesCount = dimension * entryCount;
			}
			for(int i = 0; i<mappingPara.valuesCount; i++) {
				long dw = 0;
				data.bitRead(&dw, mappingPara.valueBits);
				mappingPara.multiplicands.push_back(dw);
			}
		} else {
			//没有映射
		}
		return true;
	}
	return false;
}
long VorbisCodeBook::findEntry(long huffmanCode, long huffmanLen) {
	for(int i = 0; i<entries.size(); i++)
		if(entries[i].huffmanCode == huffmanCode && entries[i].length == huffmanLen)
			return i;
	return -1;
}
long VorbisCodeBook::decodeEntryIn(stream &sour) {
	dword goal = 0;
	long result = -1;
	for(int i = 0; i<32; i++) {
		dword oneBit = 0;
		sour.bitRead(&oneBit, 1);
		if(oneBit)
			goal |= (1 << i);
		result = findEntry(goal, i + 1);
		if(result >= 0)
			return result;
	}
	return -1;
}
long VorbisCodeBook::decodeValueIn(stream &sour) {
	long result = decodeEntryIn(sour);
	if(result >= 0)
		return entries[result].value;
	return -1;
}
sequence VorbisCodeBook::decodeVectorIn(stream &sour, int vectorLen, bool interleaved) {
	sequence seq;
	if(interleaved) {
		//间隔·使用残差模型0的进行逆量化的时候会使用，使用残差模型1的话interleaved是false
		int i, step = vectorLen / dimension;
		std::vector<sequence> table;
		for(i = 0; i<step; i++) {
			long result = decodeEntryIn(sour);
			if(result == -1)
				return seq;
			table.push_back(quantized[result]);
		}
		int o, j;
		for(i = 0, o = 0; i<dimension; i++, o += step)
			for(j = 0; o + j<vectorLen && j<step; j++)
				seq.push_back(table[j][i]);
	} else {
		int i = 0;
		while(i<vectorLen) {
			long result = decodeEntryIn(sour);
			if(result == -1)
				return seq;
			for(int j = 0; j<dimension; j++) {
				if(i<vectorLen) {
					seq.push_back(quantized[result][j]);
					i++;
				} else {
					return seq;
				}
			}
		}
	}
	return seq;
}
std::vector<sequence> VorbisCodeBook::decodeMultVectorIn(stream &sour, int vectorLen, long offset, int ch) {
	//产生多个逆量化vector，残差模型2使用
	std::vector<sequence> seqs;
	int c;
	for(c = 0; c<ch; c++)
		seqs.push_back(sequence());
	int m = (offset + vectorLen) / ch;
	int i = offset / ch;
	c = 0;
	while(i<m) {
		long result = decodeEntryIn(sour);
		if(result == -1)
			return seqs;//失败了
		for(int j = 0; j<dimension; j++) {
			if(j<m) {
				seqs[c].push_back(quantized[result][j]);
				c++;
				if(ch == c) {
					c = 0;
					i++;
				}
			}
		}
	}
	return seqs;
}
VorbisCodeBook::HuffmanNode::HuffmanNode() {
	memset(this, 0, sizeof(HuffmanNode));
}
bool VorbisCodeBook::buildTree() {
	//最大深度等于编码本中最长条目的长度
	int maxDepth = 0;
	for(int i = 0; i<entryCount; i++)
		if(entryLen[i] > maxDepth)
			maxDepth = entryLen[i];
	//建立哈夫曼树
	std::vector<HuffmanNode> tree;
	HuffmanNode rootNode;
	rootNode.weight = 1 << maxDepth;
	tree.push_back(rootNode);
	for(int i = 0; i<entryCount; i++) {
		//第一步：排除unused条目，不能放在哈夫曼树里
		if(entryLen[i] == 0)
			continue;
		//第二步：查找哈夫曼树权重最低，且满足以下条件的节点：具有悬垂节点（左右随意）、深度小于当前条目的长度
		long minWeight = 2 << maxDepth;	//初始化为最大可能的权重值
		long minID = 0;
		for(int j = 0; j<tree.size(); j++) {
			HuffmanNode &node = tree[j];
			if(node.depth >= entryLen[i])
				continue;
			if(node.leftOK && node.rightOK)
				continue;
			if(node.weight <= minWeight) {
				minWeight = node.weight;
				minID = j;
			}
		}
		//第三步：将这个节点的深度与当前条目比较，然后扩充哈夫曼树
		int expandID = minID;
		while(tree[expandID].depth < entryLen[i]) {
			HuffmanNode &node = tree[expandID];
			HuffmanNode newNode;
			newNode.code = node.code;
			if(!node.leftOK) {
				node.leftOK = true;
				newNode.depth = node.depth + 1;
				newNode.weight = node.weight - (1 << (maxDepth - node.depth - 1));
			} else if(!node.rightOK) {
				node.rightOK = true;
				newNode.depth = node.depth + 1;
				newNode.code |= (1 << node.depth);
				newNode.weight = node.weight + (1 << (maxDepth - node.depth - 1));
			}
			if(newNode.depth == entryLen[i]) {
				newNode.isLeaf = true;
				newNode.leftOK = true;
				newNode.rightOK = true;
				Entry e;
				e.huffmanCode = newNode.code;
				e.weight = newNode.weight;
				e.length = entryLen[i];
				e.originID = i;
				for(int j = 0; j<entryLen[i]; j++)
					e.codeStr[j] = e.huffmanCode & (1 << j) ? '1' : '0';
				e.codeStr[entryLen[i]] = 0;
				if(entries.size() == 0) {
					entries.push_back(e);
				} else {
					int insertID = 0;
					for(int j = 0; j<entries.size(); j++) {
						if(entries[j].weight < e.weight) {
							insertID++;
						} else {
							break;
						}
					}
					entries.insert(entries.begin() + insertID, e);
					break;
				}
			}
			tree.push_back(newNode);
			expandID = tree.size() - 1;
		}
	}
	return true;
}
bool VorbisCodeBook::unquantize() {
	VorbisCodeBookMappingPara &para = mappingPara;
	std::vector<sequence> unsortedQuantized;
	switch(mappingType) {
	case NO_LOOK_UP:
		//不存储实际值
		return false;
	case LOOK_UP_1:
		for(int j = 0; j<entryCount; j++) {
			double last = 0;
			long indexDivisor = 1;
			sequence valueVector;
			for(int i = 0; i<dimension; i++) {
				long multiplicandOffset = (j / indexDivisor) % para.valuesCount;
				valueVector.push_back(para.delta * para.multiplicands[multiplicandOffset] + para.min + last);
				if(para.seqP)
					last = valueVector[i];
				indexDivisor *= para.valuesCount;
			}
			for(int i = 0; i<dimension; i++) {
				valueVector[i] = -valueVector[i];
			}
			unsortedQuantized.push_back(valueVector);
		}
		quantized.clear();
		for(int j = 0; j<entries.size(); j++) {
			quantized.push_back(unsortedQuantized[entries[j].originID]);
		}
		return true;
	case LOOK_UP_2:
		for(int j = 0; j<entryCount; j++) {
			double last = 0;
			sequence valueVector;
			long multiplicandOffset = j * dimension;
			for(int i = 0; i<dimension; i++) {
				valueVector.push_back(para.delta * para.multiplicands[multiplicandOffset] + para.min + last);
				if(para.seqP)
					last = valueVector[i];
				multiplicandOffset++;
			}
			for(int i = 0; i<dimension; i++) {
				valueVector[i] = -valueVector[i];
			}
			unsortedQuantized.push_back(valueVector);
		}
		quantized.clear();
		for(int j = 0; j<entries.size(); j++) {
			quantized.push_back(unsortedQuantized[entries[j].originID]);
		}
		return true;
	default:
		return false;
	}
}
VorbisCodeBook::VorbisCodeBookEntry::VorbisCodeBookEntry() {
	memset(this, 0, sizeof(VorbisCodeBookEntry));
}
VorbisCodeBook::VorbisCodeBookMappingPara::VorbisCodeBookMappingPara() {
	min = 0;
	delta = 0;
	valueBits = 0;
	seqP = 0;
	valuesCount = 0;
	multiplicands.clear();
}
VorbisTimeDomain::VorbisTimeDomain() {
	reserved = 0;
}
bool VorbisTimeDomain::buildFromData(stream &data) {
	data.bitRead(&reserved, 16);
	return 0 == reserved;
}
VorbisFloor::VorbisFloorPartitionClass::VorbisFloorPartitionClass() {
	dimension = 0;
	subClasses = 0;
	masterBooks = 0;
	subClassBooks.clear();
}
VorbisFloor::VorbisFloor() {
	floorType = 0xFFFF;
	floor0.amplitudeBits = 0;
	floor0.amplitudeOffset = 0;
	floor0.bookMapSize = 0;
	floor0.booksCount = 0;
	floor0.order = 0;
	floor0.rate = 0;
	floor1.maxClass = 0;
	floor1.multiplier = 0;
	floor1.partitions = 0;
	floor1.rangeBits = 0;
	floor1.values = 0;
}
bool VorbisFloor::buildFromData(stream &data) {
	data.bitRead(&floorType, 16);
	switch(floorType) {
	case 0U:
		data.bitRead(&floor0.order, 8);
		data.bitRead(&floor0.rate, 16);
		data.bitRead(&floor0.bookMapSize, 16);
		data.bitRead(&floor0.amplitudeBits, 6);
		data.bitRead(&floor0.amplitudeOffset, 8);
		data.bitRead(&floor0.booksCount, 4);
		floor0.booksCount++;
		for(dword i = 0; i<floor0.booksCount; i++) {
			long l = 0;
			data.bitRead(&l, 8);
			floor0.bookList.push_back(l);
		}
		return true;
	case 1U:
		data.bitRead(&floor1.partitions, 5);
		floor1.maxClass = -1;
		for(dword i = 0; i<floor1.partitions; i++) {
			long l = 0;
			data.bitRead(&l, 4);
			floor1.partitionClassList.push_back(l);
			if(l > floor1.maxClass)
				floor1.maxClass = l;
		}
		for(dword i = 0; i<floor1.maxClass + 1; i++) {
			VorbisFloor::VorbisFloorPartitionClass vfpc;
			data.bitRead(&vfpc.dimension, 3);
			vfpc.dimension++;
			data.bitRead(&vfpc.subClasses, 2);
			if(vfpc.subClasses > 0) {
				data.bitRead(&vfpc.masterBooks, 8);
			}
			for(dword j = 0; j<(1 << vfpc.subClasses); j++) {
				dword l = 0;
				data.bitRead(l, 8);
				l--;
				vfpc.subClassBooks.push_back(l);
			}
			floor1.partitionClasses.push_back(vfpc);
		}
		data.bitRead(floor1.multiplier, 2);
		floor1.multiplier++;
		data.bitRead(floor1.rangeBits, 4);
		floor1.Xlist.push_back(0);
		floor1.Xlist.push_back(1 << floor1.rangeBits);
		floor1.values = 2;
		for(dword i = 0; i<floor1.partitions; i++) {
			long l1 = floor1.partitionClassList[i];
			for(dword j = 0; j<floor1.partitionClasses[l1].dimension; j++) {
				long l = 0;
				data.bitRead(&l, floor1.rangeBits);
				floor1.Xlist.push_back(l);
				floor1.values++;
			}
		}
		return true;
	default:
		return false;
	}
}
VorbisResidue::VorbisResidue() {
	residueType = 0xFFFF;
	residueType = 0;
	begin = 0;
	end = 0;
	partitionSize = 0;
	classification = 0;
	classBook = 0;
	cascade.clear();			//串行数据组，读取book使用
	books.clear();
}
bool VorbisResidue::buildFromData(stream &data) {
	data.bitRead(&residueType, 16);
	if(residueType > 2)
		return false;
	data.bitRead(&begin, 24);
	data.bitRead(&end, 24);
	data.bitRead(&partitionSize, 24);
	partitionSize++;
	data.bitRead(&classification, 6);
	classification++;
	data.bitRead(&classBook, 8);
	cascade.clear();
	for(dword i = 0; i<classification; i++) {
		uchar hb = 0;
		uchar lb = 0;
		uchar bitFlag = 0;
		data.bitRead(&lb, 3);
		data.bitRead(&bitFlag, 1);
		if(bitFlag)
			data.bitRead(&hb, 5);
		cascade.push_back(hb * 8 + lb);
	}
	for(dword i = 0; i<classification; i++) {
		queue bookElem;
		for(dword j = 0; j<8; j++) {
			if(cascade[i] & (1 << j)) {
				uchar l = 0;
				data.bitRead(&l, 8);
				bookElem.push_back(l);
			} else {
				bookElem.push_back(0);
			}
		}
		books.push_back(bookElem);
	}
	return true;
}
VorbisMapping::VorbisMapping() {
	mappingType = 0;
	submaps = 0;
	couplingSteps = 0;
	channels = 0;
	reserved = 0;
}
bool VorbisMapping::buildFromData(stream &data) {
	data.bitRead(&mappingType, 16);
	if(mappingType != 0)
		return false;
	uchar flag = 0;
	data.bitRead(&flag, 1);
	if(flag == 0) {
		submaps = 1;
	} else {
		data.bitRead(&submaps, 4);
		submaps++;
	}
	flag = 0;
	data.bitRead(&flag, 1);
	if(flag == 0) {
		couplingSteps = 0;
	} else {
		data.bitRead(&couplingSteps, 8);
		couplingSteps++;
		dword vLen = OGGsupport::ilog(channels - 1);
		for(dword i = 0; i<couplingSteps; i++) {
			PolarCoordinate pc = {0};
			data.bitRead(&pc.magnitudes, vLen);
			data.bitRead(&pc.angles, vLen);
			couplingList.push_back(pc);
		}
	}
	data.bitRead(&reserved, 2);
	if(submaps > 1) {
		for(dword i = 0; i<channels; i++) {
			long l = 0;
			data.bitRead(&l, 4);
			mux.push_back(l);
		}
	}
	for(dword i = 0; i<submaps; i++) {
		SubmapPara sp = {0};
		data.bitRead(&sp.discarded, 8);
		data.bitRead(&sp.floor, 8);
		data.bitRead(&sp.residue, 8);
		submapList.push_back(sp);
	}
	return true;
}
VorbisMode::VorbisMode() {
	blockFlag = 0;
	windowType = 0;
	transformType = 0;
	mapping = 0;
}
bool VorbisMode::buildFromData(stream &data) {
	data.bitRead(&blockFlag, 1);
	data.bitRead(&windowType, 16);
	data.bitRead(&transformType, 16);
	data.bitRead(&mapping, 8);
	return true;
}
VorbisIdentity::VorbisIdentity() {
	memset(this, 0, sizeof(VorbisIdentity));
}
VorbisBlock::VorbisBlock() {
	serial = 0;
	mode = 0;
	mapping = 0;
	blockSize = 0;
	flagLong = 0;
	flagPrevWindow = 0;
	flagNextWindow = 0;
}
OGGobject::OGGobject() {}
bool OGGobject::loadFile(const str &fileName) {
	stream s;
	s.loadFile(fileName);
	return load(s);
}
bool OGGobject::load(stream &s) {
	int b;
	//索性多申请一些
	packs.clear();
	pages.clear();
	packs.reserve(15000);
	pages.reserve(15000);
	char mark[5] = {0};
	OGGpack opk(0);
	bool packOver = true;
	//解包为逻辑流
	while(s.read(mark, 4)) {
		if(str(mark) != "OggS")
			return true;
		OGGpage op;
		s.readByte(op.ver);
		s.readByte(op.type);
		s.read(op.granule, 8);
		s.readDWord(op.serial);
		s.readDWord(op.sequence);
		s.readDWord(op.checkCRC);
		s.readByte(op.segCount);
		op.segLength.clear();
		for(int i = 0; i<op.segCount; i++) {
			uchar uTemp;
			s.readByte(uTemp);
			op.segLength.push_back(uTemp);
		}
		for(int i = 0; i<op.segCount; i++) {
			stream sTemp;
			s.readStream(sTemp, op.segLength[i]);
			op.segData.push_back(sTemp);
		}
		pages.push_back(op);
		for(int i = 0; i<op.segCount; i++) {
			opk.pushStream(op.segData[i], op.segLength[i]);
			if(op.segLength[i] != 0XFF) {
				packOver = true;
				packs.push_back(opk);
				opk.clear();
				opk.release();
				opk.allocate(0);
			} else {
				packOver = false;
			}
		}
	}
	opk.release();
	//判断包头个数
	if(packs.size()<3)
		return false;
	//读取鉴定头
	packs[0].resetPosition();
	uchar headByte = 0;
	packs[0].readByte(headByte);
	if(headByte != 0x01 || packs[0].readString(6) != "vorbis")
		return false;
	packs[0].readDWord(info.version);
	packs[0].readByte(info.channels);
	packs[0].readDWord(info.sampleRate);
	packs[0].readInt(info.bitrateMax);
	packs[0].readInt(info.bitrateNorm);
	packs[0].readInt(info.bitrateMin);
	//读取窗口长度，每个ogg里都只有长度不同的2个窗口
	uchar byteBlockSize;
	packs[0].readByte(byteBlockSize);
	info.blockSize1 = 1 << (byteBlockSize >> 4);
	info.blockSize0 = 1 << (byteBlockSize & 0x0F);
	//读取注释头
	packs[1].resetPosition();
	packs[1].readByte(headByte);
	if(headByte != 0x03 || packs[1].readString(6) != "vorbis")
		return false;
	dword strLen, otherCommentLen;
	packs[1].readDWord(strLen);
	comment.vendorInfo = packs[1].readString(strLen);
	packs[1].readDWord(otherCommentLen);
	comment.otherInfo.clear();
	for(int i = 0; i<otherCommentLen; i++) {
		packs[1].readDWord(strLen);
		comment.otherInfo.push_back(packs[1].readString(strLen));
	}
	//读取设置头
	packs[2].resetPosition();
	packs[2].readByte(headByte);
	if(headByte != 0x05 || packs[2].readString(6) != "vorbis")
		return false;
	packs[2].bitAlignPosition();
	uchar codeBookCount = 0;
	uchar timeDomainCount = 0;
	uchar floorCount = 0;
	uchar residueCount = 0;
	uchar mappingCount = 0;
	uchar modeCount = 0;
	//读取编码本
	packs[2].bitRead(&codeBookCount, 8);
	codeBookCount++;
	codeBook.clear();
	for(b = 0; b<codeBookCount; b++) {
		VorbisCodeBook vcb;
		int st[2] = {packs[2].bitGetPosition() / 8};
		if(!vcb.buildFromData(packs[2]))
			return false;
		st[1] = packs[2].bitGetPosition() / 8;
		codeBook.push_back(vcb);
	}
	//读取时域信号（在Vorbis I并没有用）
	packs[2].bitRead(&timeDomainCount, 6);
	timeDomainCount++;
	timeDomains.clear();
	for(b = 0; b<timeDomainCount; b++) {
		VorbisTimeDomain vtd;
		if(!vtd.buildFromData(packs[2]))
			return false;
		timeDomains.push_back(vtd);
	}
	//读取基底生成参数
	packs[2].bitRead(&floorCount, 6);
	floorCount++;
	floors.clear();
	for(b = 0; b<floorCount; b++) {
		VorbisFloor vf;
		if(!vf.buildFromData(packs[2]))
			return false;
		floors.push_back(vf);
	}
	//读取残差生成参数
	packs[2].bitRead(&residueCount, 6);
	residueCount++;
	residues.clear();
	for(b = 0; b<residueCount; b++) {
		VorbisResidue vr;
		if(!vr.buildFromData(packs[2]))
			return false;
		residues.push_back(vr);
	}
	//读取映射类型
	packs[2].bitRead(&mappingCount, 6);
	mappingCount++;
	mappings.clear();
	for(b = 0; b<mappingCount; b++) {
		VorbisMapping vm;
		vm.channels = info.channels;
		if(!vm.buildFromData(packs[2]))
			return false;
		mappings.push_back(vm);
	}
	//读取编码模式
	packs[2].bitRead(&modeCount, 6);
	modeCount++;
	modes.clear();
	for(b = 0; b<modeCount; b++) {
		VorbisMode vm;
		if(!vm.buildFromData(packs[2]))
			return false;
		modes.push_back(vm);
	}
	//三个数据头全部读取完毕
	return true;
}
bool OGGobject::initDecoder() {
	//blocks创建预存空间
	int i;
	blocks.reserve(packs.size());
	//给编码本创建哈夫曼树
	if(codeBook.size() == 0)
		return false;
	for(i = 0; i<codeBook.size(); i++) {
		if(!codeBook[i].buildTree())
			return false;
	}
	//计算编码本的量化参数
	for(i = 0; i<codeBook.size(); i++) {
		if(codeBook[i].mappingType != 0) {
			if(!codeBook[i].unquantize()) {
				return false;
			}
		}
	}
	//残差向量初始化
	for(i = 0; i<residues.size(); i++) {
		dword maxStage = 0;
		for(int j = 0; j<residues[i].classification; j++) {
			dword currentStage = OGGsupport::ilog(residues[i].cascade[j]);
			if(currentStage > maxStage)
				maxStage = currentStage;
		}
		residues[i].stages = maxStage;
		dword partvals = 1;
		for(int j = 0; j<codeBook[residues[i].classBook].dimension; j++)
			partvals *= residues[i].classification;
		residues[i].partvals = partvals;
		for(int j = 0; j<residues[i].partvals; j++) {
			queue pval;
			long val = j;
			long mult = partvals / residues[i].classification;
			for(int k = 0; k<codeBook[residues[i].classBook].dimension; k++) {
				long deco = val / mult;
				val -= deco*mult;
				mult /= residues[i].classification;
				pval.push_back(deco);
			}
			residues[i].decodeMaps.push_back(pval);
		}
	}
	//计算窗口的形状
	//短窗口
	for(int i = 0; i<info.blockSize0 / 2; i++) {
		windowValueShort.push_back(sin(1.5707963267948*pow(sin(1.5707963267948*(0.5 + i) / (info.blockSize0 / 2)), 2)));
	}
	//长窗口
	for(int i = 0; i<info.blockSize1 / 2; i++) {
		windowValueLong.push_back(sin(1.5707963267948*pow(sin(1.5707963267948*(0.5 + i) / (info.blockSize1 / 2)), 2)));
	}
	return true;
}
bool OGGobject::packDecode(int packID) {
	if(packID <= 2 || packID >= packs.size())
		return false;
	OGGpack &data = packs[packID];
	data.bitResetPosition();
	//第一步：判断是否是一个音频包
	bool isAudio = 0;
	data.bitRead(&isAudio, 1);
	if(isAudio)
		return false;
	VorbisBlock vb;
	vb.serial = packID - 3;
	//第二步：确定模式
	data.bitRead(&vb.mode, OGGsupport::ilog(modes.size() - 1));			//确定当前mode
	//第三步：窗口形状，输出PCM用
	vb.flagLong = modes[vb.mode].blockFlag == 1;
	vb.blockSize = modes[vb.mode].blockFlag ? info.blockSize1 : info.blockSize0;
	if(modes[vb.mode].blockFlag) {
		//这是个长窗口
		data.bitRead(&vb.flagPrevWindow, 1);
		data.bitRead(&vb.flagNextWindow, 1);
	} else {
		//这是个短窗口
		vb.flagPrevWindow = false;
		vb.flagNextWindow = false;
	}
	//第四步：基底向量
	vb.mapping = modes[vb.mode].mapping;
	VorbisMapping &vm = mappings[vb.mapping];
	vb.floorCurve.clear();					//每个通道的基底曲线
	vb.floorNoResidue.clear();				//每个通道的无残差状态
	vb.doNotDecode.clear();					//是否要decode(小于通道数)
	for(int i = 0; i<info.channels; i++) {
		long submapNum = i < vm.mux.size() ? vm.mux[i] : 0;
		long currentFloor = vm.submapList[submapNum].floor;
		VorbisFloor &vf = floors[currentFloor];
		VorbisFloorCurve vfc;
		if(0 == floors[currentFloor].floorType) {
			//第一种生成基底的方式，太复杂也基本不会用，可能(肯定)会有BUG
			int amplitude;
			data.bitRead(&amplitude, vf.floor0.amplitudeBits);
			if(amplitude == 0) {
				vb.floorCurve.push_back(vfc);
				vb.floorNoResidue.push_back(true);
				continue;
			}
			sequence coefficients;
			long bookNum;
			data.bitRead(&bookNum, OGGsupport::ilog(vf.floor0.booksCount));
			if(bookNum >= codeBook.size())
				return false;
			double last = 0;
			while(coefficients.size() < vf.floor0.order) {
				VorbisCodeBook &b = codeBook[vf.floor0.bookList[bookNum]];
				sequence tempVector = b.decodeVectorIn(data, vf.floor0.order, false);
				for(int j = 0; j<tempVector.size(); j++) {
					tempVector[j] += last;
				}
				last = tempVector[tempVector.size() - 1];
				for(int j = 0; j<tempVector.size(); j++) {
					coefficients.push_back(tempVector[j]);
				}
			}
			queue seqMap;
			int n = vb.blockSize / 2;
			for(int j = 0; j<n; j++)
				vfc.floorCurve.push_back(0);
			for(int j = 0; j<n; j++) {
				if(j == n - 1) {
					seqMap.push_back(-1);
					break;
				}
				double x = (double)vf.floor0.rate * j / (2 * n);
				double bark1 = 13.1*atan(0.00074*x) + 2.24*atan(0.0000000185*x*x) + 0.0001*x;
				x = (double)vf.floor0.rate * 0.5;
				double bark2 = 13.1*atan(0.00074*x) + 2.24*atan(0.0000000185*x*x) + 0.0001*x;
				seqMap.push_back((long)MIN(floor((double)vf.floor0.bookMapSize * bark1 / bark2), vf.floor0.bookMapSize - 1));
			}
			for(int j = 0; j<n;) {
				double omg = 3.1415926536 * seqMap[j] / vf.floor0.bookMapSize;
				double comg = cos(omg);
				double p, q;
				if(vf.floor0.order % 2) {
					p = 1.0 - comg * comg;
					q = 0.25;
					for(int k = 0; k<(vf.floor0.order - 3) / 2; k++)
						p *= 4.0*(cos(coefficients[2 * k + 1]) - comg)*(cos(coefficients[2 * k + 1]) - comg);
					for(int k = 0; k<(vf.floor0.order - 1) / 2; k++)
						q *= 4.0*(cos(coefficients[2 * k]) - comg)*(cos(coefficients[2 * k]) - comg);
				} else {
					p = (1.0 - comg) / 2;
					q = (1.0 + comg) / 2;
					for(int k = 0; k<(vf.floor0.order - 2) / 2; k++)
						p *= 4.0*(cos(coefficients[2 * k + 1]) - comg)*(cos(coefficients[2 * k + 1]) - comg);
					for(int k = 0; k<(vf.floor0.order - 2) / 2; k++)
						q *= 4.0*(cos(coefficients[2 * k]) - comg)*(cos(coefficients[2 * k]) - comg);
				}
				double floorValue = exp(0.11512925*(amplitude*vf.floor0.amplitudeOffset / sqrt(p + q) / ((1 << vf.floor0.amplitudeBits) - 1) - vf.floor0.amplitudeOffset));
				int iter;
				do {
					iter = seqMap[j];
					vfc.floorCurve[j] = floorValue;
					j++;
				} while(iter == seqMap[j]);
			}
		} else if(1 == floors[currentFloor].floorType) {
			//第二种生成基底的方式
			data.bitRead(&vfc.flagNonzero, 1);
			if(!vfc.flagNonzero) {
				vb.floorCurve.push_back(vfc);
				vb.floorNoResidue.push_back(true);
				continue;
			}
			long r[4] = {256, 128, 86, 64};
			vfc.range = r[vf.floor1.multiplier - 1];
			dword firstElem = 0;
			dword secondElem = 0;
			data.bitRead(&firstElem, OGGsupport::ilog(vfc.range - 1));
			data.bitRead(&secondElem, OGGsupport::ilog(vfc.range - 1));
			vfc.Ylist.clear();
			vfc.Ylist.push_back(firstElem);
			vfc.Ylist.push_back(secondElem);
			for(int j = 0; j<vf.floor1.partitions; j++) {
				long classs = vf.floor1.partitionClassList[j];
				long cdim = vf.floor1.partitionClasses[classs].dimension;
				long cbits = vf.floor1.partitionClasses[classs].subClasses;
				long csub = (1 << cbits) - 1;
				long cvals = 0;
				if(cbits>0) {
					//查表
					long bookNum = vf.floor1.partitionClasses[classs].masterBooks;
					cvals = codeBook[bookNum].decodeValueIn(data);
				}
				for(int k = 0; k<cdim; k++) {
					long bookNum = vf.floor1.partitionClasses[classs].subClassBooks[cvals & csub];
					cvals >>= cbits;
					if(bookNum >= 0) {
						vfc.Ylist.push_back(codeBook[bookNum].decodeValueIn(data));
					} else {
						vfc.Ylist.push_back(0);
					}
				}
			}
			//整合曲线step1
			vfc.step2Flag.push_back(1);
			vfc.step2Flag.push_back(1);
			vfc.finalYlist.push_back(vfc.Ylist[0]);
			vfc.finalYlist.push_back(vfc.Ylist[1]);
			for(int j = 2; j<vf.floor1.values; j++) {
				int LNO = OGGsupport::lowNeighbor(vf.floor1.Xlist, j);
				int HNO = OGGsupport::highNeighbor(vf.floor1.Xlist, j);
				int predicted = OGGsupport::renderPoint(
					vf.floor1.Xlist[LNO], vfc.finalYlist[LNO],
					vf.floor1.Xlist[HNO], vfc.finalYlist[HNO],
					vf.floor1.Xlist[j]);
				int val = vfc.Ylist[j];
				int highroom = vfc.range - predicted;
				int lowroom = predicted;
				int room = 2 * min(highroom, lowroom);
				if(val == 0) {
					vfc.step2Flag.push_back(0);
					vfc.finalYlist.push_back(predicted);
				} else {
					vfc.step2Flag[LNO] = 1;
					vfc.step2Flag[HNO] = 1;
					vfc.step2Flag.push_back(1);
					vfc.finalYlist.push_back(
						val >= room ?
						(highroom > lowroom ? val - lowroom + predicted : predicted - val + highroom - 1) :
						((val % 2 == 0) ? (predicted + val / 2) :
						(predicted - (val + 1) / 2)));
				}
			}
			//整合曲线step2
			//先要对Xlist进行排序，然后以相同的排序方式重新排列finalYlist和step2Flag
			for(int j = 0; j<vb.blockSize / 2; j++)
				vfc.floorCurve.push_back(0);
			queue sortedIndex = OGGsupport::qSort(vf.floor1.Xlist);
			queue sortedXlist = OGGsupport::qResort(vf.floor1.Xlist, sortedIndex);
			queue sortedYlist = OGGsupport::qResort(vfc.finalYlist, sortedIndex);
			queue sortedYFlag = OGGsupport::qResort(vfc.step2Flag, sortedIndex);
			int hx = 0;
			int lx = 0;
			int ly = sortedYlist[0] * vf.floor1.multiplier;
			int hy;
			//整合曲线得到dB值
			for(int j = 1; j<vf.floor1.values; j++) {
				if(sortedYFlag[j]) {
					hy = sortedYlist[j] * vf.floor1.multiplier;
					hx = sortedXlist[j];
					OGGsupport::renderLine(lx, ly, hx, hy, vfc.floorCurve);
					lx = hx;
					ly = hy;
				}
			}
			//如果设定正确（曲线的定义域等于窗口长度的一半）则下面代码没用。
			if(hx < vfc.floorCurve.size()) {
				OGGsupport::renderLine(hx, hy, vfc.floorCurve.size(), hy, vfc.floorCurve);
			} else {
				vfc.floorCurve.erase(vfc.floorCurve.begin() + hx, vfc.floorCurve.end());
			}
		} else {
			//FloorType只支持0和1
			return false;
		}
		vb.floorCurve.push_back(vfc);
		vb.floorNoResidue.push_back(false);
	}
	//第五步解码残差向量
	for(int i = 0; i<info.channels; i++) {
		sequence seq;
		for(int j = 0; j<vb.blockSize / 2; j++)
			seq.push_back(0);
		vb.residueVector.push_back(seq);
	}
	for(int i = 0; i<vm.submaps; i++) {
		long ch = 0;
		for(int j = 0; j<info.channels; j++) {
			if((j >= vm.mux.size() && i == 0) || i == vm.mux[j]) {
				vb.doNotDecode.push_back(vb.floorNoResidue[j]);
				ch++;
			}
		}
		long residueNum = vm.submapList[i].residue;
		VorbisResidue &vr = residues[residueNum];
		long residueType = vr.residueType;
		long actualSize = vb.blockSize / 2;
		if(vr.residueType == 2)
			actualSize *= info.channels;
		long cwPerCodeword = codeBook[vr.classBook].dimension;
		long nToRead = ((vr.end < actualSize) ? vr.end : actualSize) - vr.begin;
		long partToRead = nToRead / vr.partitionSize;
		long partWords = (partToRead + cwPerCodeword - 1) / cwPerCodeword;
		if(nToRead == 0)
			continue;
		std::vector<std::vector<queue>> partWord;
		switch(vr.residueType) {
		case 0:
		case 1:
			for(int j = 0; j<ch; j++) {
				partWord.push_back(std::vector<queue>());
				partWord.push_back(std::vector<queue>());
			}
			for(int stage = 0; stage<vr.stages; stage++) {
				for(int p = 0, l = 0; p<partToRead; l++) {
					if(stage == 0) {
						for(int c = 0; c<ch; c++) {
							int temp = codeBook[vr.classBook].decodeValueIn(data);
							if(temp == -1 || temp >= vr.partvals)
								return false;
							if(temp >= vr.decodeMaps.size())
								return false;
							partWord[c].push_back(vr.decodeMaps[temp]);
						}
					}
					for(int cw = 0; cw<cwPerCodeword && p<partToRead; cw++, p++) {
						for(int c = 0; c<ch; c++) {
							long offset = vr.begin + p * vr.partitionSize;
							if(vr.cascade[partWord[c][l][cw]] & (1 << stage)) {
								int book = vr.books[partWord[c][l][cw]][stage];
								if(book > 0) {
									VorbisCodeBook &thisBook = codeBook[book];
									sequence seq = thisBook.decodeVectorIn(data, vr.partitionSize, vr.residueType == 0);
									for(int sq = 0; sq<seq.size(); sq++) {
										vb.residueVector[c][offset + sq] += seq[sq];
									}
								}
							}
						}
					}
				}
			}
			break;
		case 2:
			partWord.push_back(std::vector<queue>());
			for(int stage = 0; stage<vr.stages; stage++) {
				for(int p = 0, l = 0; p<partToRead; l++) {
					if(stage == 0) {
						int temp = codeBook[vr.classBook].decodeValueIn(data);
						if(temp == -1 || temp >= vr.partvals)
							return false;
						if(temp >= vr.decodeMaps.size())
							return false;
						partWord[0].push_back(vr.decodeMaps[temp]);
					}
					for(int cw = 0; cw<cwPerCodeword && p<partToRead; cw++, p++) {
						long offset = vr.begin + p * vr.partitionSize;
						if(vr.cascade[partWord[0][l][cw]] & (1 << stage)) {
							int book = vr.books[partWord[0][l][cw]][stage];
							if(book > 0) {
								VorbisCodeBook &thisBook = codeBook[book];
								std::vector<sequence> seqs = thisBook.decodeMultVectorIn(data, vr.partitionSize, vr.begin + p * vr.partitionSize, ch);
								for(int c = 0; c<ch; c++) {
									for(int sq = 0; sq<seqs[c].size(); sq++) {
										vb.residueVector[c][offset / ch + sq] += seqs[c][sq];
									}
								}
							}
						}

					}
				}
			}
		}
	}
	//第六步逆耦合·绝大部分没卵用
	if(vm.couplingSteps > 0) {
		queue M, A;
		for(int i = 0; i<vm.couplingSteps; i++) {
			M.push_back(vm.couplingList[i].magnitudes);
			A.push_back(vm.couplingList[i].angles);
		}
		for(int i = 0; i<vm.couplingSteps; i++) {
			if(vb.floorNoResidue[M[i]] || vb.floorNoResidue[A[i]]) {
				vb.floorNoResidue[M[i]] = true;
				vb.floorNoResidue[A[i]] = true;
			}
		}
		for(int i = vm.couplingSteps - 1; i >= 0; i--) {
			sequence residueVectorM = vb.residueVector[M[i]];
			sequence residueVectorA = vb.residueVector[A[i]];
			for(int j = 0; j<residueVectorM.size(); j++) {
				double mOld = residueVectorM[j];
				double aOld = residueVectorA[j];
				double mNew, aNew;
				if(mOld>0) {
					if(aOld>0) {
						mNew = mOld;
						aNew = mOld - aOld;
					} else {
						aNew = mOld;
						mNew = mOld + aOld;
					}
				} else if(aOld > 0) {
					mNew = mOld;
					aNew = mOld + aOld;
				} else {
					aNew = mOld;
					mNew = mOld - aOld;
				}
				residueVectorM[j] = mNew;
				residueVectorA[j] = aNew;
			}
			vb.residueVector[M[i]] = residueVectorM;
			vb.residueVector[A[i]] = residueVectorA;
		}
	}
	//第七步·计算基底向量和残差向量点积获得光谱向量，基底向量要通过查表从分贝值转化为能量值
	vb.spectrumVector.clear();
	for(int i = 0; i<info.channels; i++) {
		sequence v;
		for(int j = 0; j<vb.blockSize / 2; j++) {
			if(vb.doNotDecode[i]) {
				v.push_back(0);
			} else {
				v.push_back(vb.residueVector[i][j] * OGGsupport::invDb(vb.floorCurve[i].floorCurve[j]));
			}
		}
		vb.spectrumVector.push_back(v);
	}
	//第八步·执行逆离散余弦变换·得到初始PCM流
	vb.pcmVector.clear();
	for(int i = 0; i<info.channels; i++) {
		double *in = new double[vb.blockSize];
		memset(in, 0, vb.blockSize*sizeof(double));
		memcpy(in, vb.spectrumVector[i].data(), vb.spectrumVector[i].size()*sizeof(double));
		MDCT m;
		m.initial(vb.blockSize);
		m.backward(in, in);
		m.destory();
		sequence v;
		for(int j = 0; j<vb.blockSize; j++)
			v.push_back(in[j]);
		vb.pcmVector.push_back(v);
		delete[] in;
	}
	//第九步·窗口化后叠加覆盖
	//需要两个块同时运作，不在这进行了，将其压入blocks序列后，在下面进行
	blocks.push_back(vb);
	return true;
}
///////////////////////////////////////////////////
long OGGobject::initPCM() {
	sequence seq;
	seq.reserve(pages[pages.size() - 1].sampleTotalCount);
	pcm.clear();
	for(int ch = 0; ch<info.channels; ch++)
		pcm.push_back(seq);
	return 0;
}
long OGGobject::makePCMstart() {
	const VorbisBlock &b = blocks[0];
	const int longSize = info.blockSize1 / 2;
	const int shortSize = info.blockSize0 / 2;
	const sequence &winValue = b.flagLong ? windowValueLong : windowValueShort;
	const int len = b.flagLong ? longSize : shortSize;
	for(int ch = 0; ch<info.channels; ch++) {
		for(int i = 0; i<len; i++) {
			pcm[ch].push_back(winValue[i] * b.pcmVector[ch][i]);
		}
	}
	return pcm[0].size();
}
long OGGobject::makePCMend() {
	const VorbisBlock &b = blocks[1];
	const int longSize = info.blockSize1 / 2;
	const int shortSize = info.blockSize0 / 2;
	const sequence &winValue = b.flagLong ? windowValueLong : windowValueShort;
	const int len = b.flagLong ? longSize : shortSize;
	for(int ch = 0; ch<info.channels; ch++) {
		for(int i = 0; i<len; i++) {
			pcm[ch].push_back(winValue[len - 1 - i] * b.pcmVector[ch][len - 1 - i]);
		}
	}
	return pcm[0].size();
}
long OGGobject::makePCM(int blockID) {
	if(blockID == 0 || blockID >= blocks.size())
		return pcm[0].size();
	const VorbisBlock &b1 = blocks[blockID - 1];
	const VorbisBlock &b2 = blocks[blockID];
	const int longSize = info.blockSize1 / 2;
	const int shortSize = info.blockSize0 / 2;
	for(int ch = 0; ch<info.channels; ch++) {
		//长短相同
		if(b1.flagLong == b2.flagLong) {
			const bool flagLong = b1.flagLong;
			const sequence winValue = flagLong ? windowValueLong : windowValueShort;
			const int len = flagLong ? longSize : shortSize;
			for(int i = 0; i<len; i++) {
				double value = 0;
				value += winValue[len - 1 - i] * b1.pcmVector[ch][i + len];
				value += winValue[i] * b2.pcmVector[ch][i];
				pcm[ch].push_back(value);
			}
		} else {
			//前短后长，先插入交叉部分（长度是短窗口的长度/2），再以满能量的方式插入后面的部分（长度是两个窗口长度相减/4）
			const sequence &winValue = windowValueShort;
			int len;
			if(!b1.flagLong) {
				len = shortSize;
				for(int i = 0; i<len; i++) {
					double value = 0;
					value += winValue[len - 1 - i] * b1.pcmVector[ch][i + len];
					value += winValue[i] * b2.pcmVector[ch][i + (longSize - shortSize) / 2];
					pcm[ch].push_back(value);
				}
				len = (longSize - shortSize) / 2;
				for(int i = 0; i<len; i++) {
					double value = 0;
					value += b2.pcmVector[ch][i + (longSize + shortSize) / 2];
					pcm[ch].push_back(value);
				}
			} else {
				len = (longSize - shortSize) / 2;
				for(int i = 0; i<len; i++) {
					double value = 0;
					value += b1.pcmVector[ch][longSize + i];
					pcm[ch].push_back(value);
				}
				len = shortSize;
				for(int i = 0; i<len; i++) {
					double value = 0;
					value += winValue[len - 1 - i] * b1.pcmVector[ch][longSize + (longSize - shortSize) / 2 + i];
					value += winValue[i] * b2.pcmVector[ch][i];
					pcm[ch].push_back(value);
				}
			}
		}
	}
	return pcm[0].size();
}

long OGGobject::makePCMstream(stream &s) {
	s.allocate(pcm[0].size()*info.channels * 2);
	for(int i = 0; i<pcm[0].size(); i++)
		for(int j = 0; j<info.channels; j++) {
		int value = floor(pcm[j][i] * 32767.0F + 0.5);
		if(value > 32767)
			value = 32767;
		if(value < -32767)
			value = -32767;
		s.pushWord((short)value);
		}
	return s.length;
}
void OGGobject::release() {
	pages.clear();
	packs.clear();
	codeBook.clear();
	timeDomains.clear();
	floors.clear();
	residues.clear();
	mappings.clear();
	modes.clear();
	windowValueShort.clear();
	windowValueLong.clear();
	blocks.clear();
	pcm.clear();
	memset(&info, 0, sizeof(VorbisIdentity));
	comment.vendorInfo.clear();
	comment.otherInfo.clear();
}

bool KoishiAudioTool::loadWAV(audio &ad, const str &fileName) {
	stream s;
	if(!s.loadFile(fileName))
		return false;
	return loadWAV(ad, s);
}
bool KoishiAudioTool::loadWAV(audio &ad, const stream &fileStream) {
	WAVobject wo;
	stream s = fileStream;
	if(!wo.load(s))
		return false;
	s.release();
	return loadWAV(ad, wo);
}
bool KoishiAudioTool::loadWAV(audio &ad, const WAVobject &wo) {
	switch(wo.bitPerSample) {
	case 16:
		ad.create(wo.rawData, wo.channels, wo.sampleRate);
		return true;
	case 8:
	{
		stream modifiedRawData;
		modifiedRawData.allocate(wo.rawData.length * 2);
		for(int i = 0; i<wo.rawData.length; i++) {
			if(wo.rawData[i] & 0x80) {
				modifiedRawData.pushByte(0);
				modifiedRawData.pushByte(wo.rawData[i] - 0x80);
			} else {
				modifiedRawData.pushByte(0xFF);
				modifiedRawData.pushByte(wo.rawData[i] - 0x80);
			}
		}
		ad.create(modifiedRawData, wo.channels, wo.sampleRate);
		return true;
	}
	}
	return false;
}
bool KoishiAudioTool::makeWAV(const audio &ad, const str &fileName) {
	stream s;
	makeWAV(ad, s);
	s.makeFile(fileName);
	return true;
}
bool KoishiAudioTool::makeWAV(const audio &ad, stream &fileStream) {
	WAVobject wo;
	wo.channels = ad.channel;
	wo.audioFormat = 1;
	wo.bitPerSample = 16;
	wo.byteAlign = ad.channel * 2;
	wo.extraInfo = 0;
	wo.sampleRate = ad.sampleRate;
	wo.byteRate = ad.channel * wo.sampleRate * wo.bitPerSample / 8;
	wo.rawData.allocate(ad.length * ad.channel * 2 + 1000);
	for(int i = 0; i<ad.length; i++)
		for(int j = 0; j<ad.channel; j++)
			wo.rawData.pushWord(ad[i][j]);
	wo.make(fileStream);
	return true;
}
bool KoishiAudioTool::loadOGG(audio &ad, const str &fileName) {
	stream s;
	if(!s.loadFile(fileName))
		return false;
	return loadOGG(ad, s);
}
bool KoishiAudioTool::loadOGG(audio &ad, const stream &fileStream) {
	OGGobject oo;
	stream s = fileStream;
	if(!oo.load(s))
		return false;
	if(!oo.initDecoder())
		return false;
	return loadOGG(ad, oo);
}
bool KoishiAudioTool::loadOGG(audio &ad, OGGobject &oo) {
	stream s;
	oo.initPCM();
	int i = 3;
	int j = 0;
	while(oo.packDecode(i++))
		oo.makePCM(j++);
	oo.makePCMstream(s);
	if(s.length == 0)
		return false;
	ad.create(s, oo.info.channels, oo.info.sampleRate);
	return true;
}


//////////////////////////////////////