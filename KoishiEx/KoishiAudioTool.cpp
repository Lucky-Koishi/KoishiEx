#include "StdAfx.h"
#include "KoishiAudioTool.h"
#include "KoishiImageTool.h"
#include "KoishiNeoplePack.h"

#include <math.h>
#include <stdlib.h>
#include "../General/lib_audio/codec.h"
#include "../General/lib_audio/vorbisenc.h"
#pragma comment(lib, "../General/lib_audio/libogg.lib")
#pragma comment(lib, "../General/lib_audio/libvorbis.lib")

using namespace Koishi;
using namespace KoishiAudioTool;
using namespace KoishiAudioTool::WAV;

//傅里叶变换
void KoishiAudioTool::FFT(complex*a, int n){
	int bit = 0;
	while((1<<bit)<n)
		bit ++;
	int *rev = new int[n];
	memset(rev, 0, sizeof(int)*n);
	for(int i = 0;i<n;i++){
		rev[i] = (rev[i>>1]>>1)|((i&1)<<(bit-1));
		if(i<rev[i]){
			complex a1 = a[i];
			a[i] = a[rev[i]];
			a[rev[i]] = a1;
		}
	}
	for(int mid = 1;mid<n;mid*=2){
		complex temp(cos(3.1415926536f / mid), /*(inv?-1:1)*/sin(3.1415926536f / mid));
		for(int i = 0;i<n;i+=mid*2){
			complex omega(1);
			for(int j = 0;j<mid;j++,omega=omega*temp){
				complex x = a[i+j];
				complex y = omega*a[i+j+mid];
				a[i+j] = x+y;
				a[i+j+mid] = x-y;
			}
		}
	}
	delete[] rev;
}
void KoishiAudioTool::FFT(double*a, int n){
	int bit = 0;
	while((1<<bit)<n)
		bit ++;
	int *rev = new int[n];
	memset(rev, 0, sizeof(int)*n);
	for(int i = 0;i<n;i++){
		rev[i] = (rev[i>>1]>>1)|((i&1)<<(bit-1));
		if(i<rev[i]){
			double a1 = a[i];
			a[i] = a[rev[i]];
			a[rev[i]] = a1;
		}
	}
	complex*c = new complex[n];
	for(int i = 0;i<n;i++)
		c[i] = complex(a[i]);
	for(int mid = 1;mid<n;mid*=2){
		complex temp(cos(3.1415926536f / mid), /*(inv?-1:1)*/sin(3.1415926536f / mid));
		for(int i = 0;i<n;i+=mid*2){
			complex omega(1);
			for(int j = 0;j<mid;j++,omega=omega*temp){
				complex x = c[i+j];
				complex y = omega*c[i+j+mid];
				c[i+j] = x+y;
				c[i+j+mid] = x-y;
			}
		}
	}
	for(int i = 0;i<n;i++)
		a[i] = *c[i];
	delete[] c;
	delete[] rev;
}
//
void KoishiAudioTool::makeWaveGraph(const audio &ad, int channels, image &mat, int width, int height){
	audio cad = ad;
	mat.create(height, width);
	mat.fill(color(0xFF,0x66,0x99,0xFF));
	mat.line(point(0,height/4), point(width-1,height/4),color(0xFF,0x77,0xAA,0xFF));
	mat.line(point(0,height*3/4), point(width-1,height*3/4),color(0xFF,0x77,0xAA,0xFF));
	for(int i = 0;i<width*height;i++){
		int x = i % width;
		int y = i / width;
		int xd = ad.length * x / width;
		int yd = 32768 - 65536 * y / (height / 2);
		if( yd >= -abs(cad[xd][0]) && yd <= abs(cad[xd][0])){
			mat.setElem(i, color(0xFF, 0x66, 0xFF, 0x99));
		}else if(yd + 65536 >= -abs(cad[xd][1]) && yd + 65536 <= abs(cad[xd][1])){
			mat.setElem(i, color(0xFF, 0xFF, 0xFF, 0xCC));
		}
	}
	mat.rectangle(point(0,0), point(width-1,height-1),color(0xFF,0,0,0));
	mat.line(point(0,height/2), point(width-1,height/2),color(0xFF,0,0,0));
	return;
}
void KoishiAudioTool::makeWaveGraphDB(const audio &ad, int channels, image &mat, int width, int height){
	audio cad = ad;
	mat.create(height, width);
	mat.fill(color(0xFF,0x66,0x99,0xFF));
	mat.line(point(0,height/4), point(width-1,height/4),color(0xFF,0x77,0xAA,0xFF));
	mat.line(point(0,height*3/4), point(width-1,height*3/4),color(0xFF,0x77,0xAA,0xFF));
	for(int i = 0;i<width*height;i++){
		int x = i % width;
		int y = i / width;
		int xd = ad.length * x / width;
		int yd = 100 - 200 * y / (height / 2);
		int db1 = 20 * log10(1.0F*abs(cad[xd][0]));
		int db2 = 20 * log10(1.0F*abs(cad[xd][1]));
		if( yd >= -db1 && yd <= db1){
			mat.setElem(i, color(0xFF, 0x66, 0xFF, 0x99));
		}else if(yd + 200 >= -db2 && yd + 200 <= db2){
			mat.setElem(i, color(0xFF, 0xFF, 0xFF, 0xCC));
		}
	}
	mat.rectangle(point(0,0), point(width-1,height-1),color(0xFF,0,0,0));
	mat.line(point(0,height/2), point(width-1,height/2),color(0xFF,0,0,0));
	return;
}
KoishiNeoplePack::SNDversion KoishiAudioTool::checkAudioFormat(stream &sour) {
	long r;
	sour.resetPosition();
	sour.readInt(r);
	if(r == 0x706F654E) {
		return KoishiNeoplePack::VIMAGE;
	} else if(r == 0x5367674F/*OggS*/) {
		return KoishiNeoplePack::VVORBIS;
	} else if(r == 0x46464952/*RIFF*/) {
		return KoishiNeoplePack::VWAVE;
	} else if((r & 0xFFFFFF) == 0x334449 /*ID3*/|| (r & 0xF0FF) == 0xF0FF/*MP3帧同步信号*/) {
		return KoishiNeoplePack::VMP3;
	}
	return KoishiNeoplePack::VSNDUKNOWN;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////
bool WAVobject::decode(stream &s) {
	s.resetPosition();
	s.read(info.magic, 4);
	info.magic[4] = 0;
	s.readDWord(info.size);
	s.read(info.type, 4);
	info.type[4] = 0;
	dword chunkType;
	while(s.readDWord(chunkType)){
		WAVchunk wc;
		memcpy(wc.magic, &chunkType, 4);
		wc.magic[4] = 0;
		s.readDWord(wc.size);
		s.readStream(wc.data, wc.size);
		chunk.push_back(wc);
		if(str(wc.magic) == "fmt "){
			wc.data.resetPosition();
			wc.data.readWord(audioFormat);
			wc.data.readWord(channels);
			wc.data.readInt(sampleRate);
			wc.data.readInt(byteRate);
			wc.data.readWord(byteAlign);
			wc.data.readWord(bitPerSample);
			extraInfo	 = -1;
		}
		if(str(wc.magic) == "fact"){
			wc.data.resetPosition();
			wc.data.readInt(extraInfo);
		}
		if(str(wc.magic) == "data"){
			rawData = wc.data;
		}
	}
	return true;
}

bool WAVobject::decodeFile(const str &fileName) {
	stream s;
	s.loadFile(fileName);
	return decode(s);
}
bool WAVobject::encode(stream &s){
	s.allocate(rawData.length+1000);
	s.pushString("RIFF");
	s.pushDWord(rawData.length + 36);
	s.pushString("WAVE");
	s.pushString("fmt ");
	s.pushDWord(16);
	s.pushWord(audioFormat);
	s.pushWord(channels);
	s.pushInt(sampleRate);
	s.pushInt(byteRate);
	s.pushWord(byteAlign);
	s.pushWord(bitPerSample);
	s.pushString("data");
	s.pushDWord(rawData.length);
	s.pushStream(rawData, rawData.length);
	return true;
}
bool WAVobject::encodeToFile(const str &fileName) {
	stream dest;
	if(!encode(dest))
		return false;
	if(!dest.makeFile(fileName))
		return false;
	return true;
}
bool WAVobject::makeAudio(audio &ad) {
	if(bitPerSample != 16 && bitPerSample != 8)
		return false;
	ad.destory();
	//字流
	if(bitPerSample == 16) {
		ad.create(rawData, channels, sampleRate);
		return true;
	}
	//字节流
	stream modifiedRawData;
	modifiedRawData.allocate(rawData.length * 2);
	for(int i = 0; i<rawData.length; i++) {
		if(rawData[i] & 0x80) {
			modifiedRawData.pushByte(0);
			modifiedRawData.pushByte(rawData[i] - 0x80);
		} else {
			modifiedRawData.pushByte(0xFF);
			modifiedRawData.pushByte(rawData[i] - 0x80);
		}
	}
	ad.create(modifiedRawData, channels, sampleRate);
	return true;
}
bool WAVobject::decodeAndMake(stream &source, audio &ad) {
	if(!decode(source))
		return false;
	if(!makeAudio(ad))
		return false;
	return true;
}
bool WAVobject::decodeFileAndMake(const str &fileName, audio &ad) {
	stream source;
	if(!source.loadFile(fileName))
		return false;
	return decodeAndMake(source, ad);
}

bool WAVobject::loadAudio(const audio &ad) {
	channels = ad.channel;
	audioFormat = 1;
	bitPerSample = 16;
	byteAlign = ad.channel * 2;
	extraInfo = 0;
	sampleRate = ad.sampleRate;
	byteRate = (ad.channel * sampleRate * bitPerSample) >> 3;
	rawData.allocate(ad.length * ad.channel * 2 + 1000);
	for(int i = 0; i<ad.length; i++)
		for(int j = 0; j<ad.channel; j++)
			rawData.pushWord(ad[i][j]);
	return true;
}
bool WAVobject::loadAndEncode(const audio &ad, stream &dest) {
	if(!loadAudio(ad))
		return false;
	if(!encode(dest))
		return false;
	return true;
}
bool WAVobject::loadAndEncodeToFile(const audio &ad, const str &fileName) {
	stream dest;
	if(!loadAndEncode(ad, dest))
		return false;
	if(!dest.makeFile(fileName))
		return false;
	return true;
}
/////////////////////////////////////////////////////////////////////
PCMdevice::PCMdevice(){
	playing = false;
	working = false;
	recording = false;
	energyLeft = 0;
	energyRight = 0;
	for(int i = 0;i<16;i++)
		freq[i] = 0;
}
void PCMdevice::resetEnergy(){
	energyLeft = 0;
	energyRight = 0;
	for(int i = 0;i<16;i++)
		freq[i] = 0;
}
void PCMdevice::updateEnergy(LPWAVEHDR lpWaveHeader){
	if(waveFormat.nChannels > 0 && lpWaveHeader->dwBufferLength >= 4){
		int a = 0, b = 0;
		for(int i = 0;i<lpWaveHeader->dwBufferLength-3;i+=2*waveFormat.nChannels){
			short a1 = abs((short)(lpWaveHeader->lpData[i] | lpWaveHeader->lpData[i+1] << 8));
			short b1 = abs((short)(lpWaveHeader->lpData[i+2] | lpWaveHeader->lpData[i+3] << 8));
			a = a1 > a ? a1  : a;
			b = b1 > b ? b1 : b;
		}
		energyLeft = a ;
		energyRight = b ;
		//频谱
		int len = lpWaveHeader->dwBufferLength/2;
		double *d = new double[MAXSIZE];
		memset(d, 0, sizeof(double)*MAXSIZE);
		for(int i = 0;i<len;i++)
			d[i] = abs((short)(lpWaveHeader->lpData[2*i] | lpWaveHeader->lpData[2*i+1] << 8))/32767.f;
		FFT(d, MAXSIZE);
		for(int i = 0;i<16;i++){
			freq[i] = 0;
			for(int j = 0;j<MAXSIZE/32;j++){
				freq[i] += d[MAXSIZE/32*i+j];
			}
		}
		delete[] d;
	}
}
void PCMdevice::initFormat(int channels, int bitPerSample, int sampleRate, int byteRate, int byteAlign, int cbSize){
	ZeroMemory(&waveFormat, sizeof(WAVEFORMATEX));
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nChannels = channels;
	waveFormat.wBitsPerSample = bitPerSample;
	waveFormat.nSamplesPerSec = sampleRate;
	waveFormat.nAvgBytesPerSec = byteRate;
	waveFormat.nBlockAlign = byteAlign;
	waveFormat.cbSize = cbSize;
}

//bool PCMdevice::initFormat(const WAV::WAVobject &PCMwavObject){
//	if(PCMwavObject.audioFormat != 1)
//		return false;
//	ZeroMemory(&waveFormat, sizeof(WAVEFORMATEX));
//	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
//	waveFormat.nChannels = PCMwavObject.channels;
//	waveFormat.wBitsPerSample = PCMwavObject.bitPerSample;
//	waveFormat.nSamplesPerSec = PCMwavObject.sampleRate;
//	waveFormat.nAvgBytesPerSec = PCMwavObject.byteRate;
//	waveFormat.nBlockAlign = PCMwavObject.byteAlign;
//	waveFormat.cbSize = PCMwavObject.extraInfo;
//	return true;
//}
dword PCMdevice::play(const stream &cPCMstream){
	playing = true;
	resetEnergy();
	PCMstream = cPCMstream;
	PCMstream.resetPosition();
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, (DWORD_PTR)callBackFuncO, (DWORD_PTR)this, CALLBACK_FUNCTION);//打开一个给定的波形音频输出装置来进行声音播放，方式为回调函数方式。如果是对话框程序，可以将第五个参数改为(DWORD)this，操作跟本Demo程序相似
	waveHeader.dwLoops = 0L;//播放区一
	waveHeader.lpData = new char[MAXSIZE];
	waveHeader.dwBufferLength = PCMstream.read(waveHeader.lpData, MAXSIZE);
	waveHeader.dwFlags = 0L;
	waveHeader2.dwLoops = 0L;//播放区二，基本同上
	waveHeader2.lpData = new char[MAXSIZE];
	waveHeader2.dwBufferLength = PCMstream.read(waveHeader2.lpData, MAXSIZE);
	waveHeader2.dwFlags = 0L;
	working = true;
	resetEnergy();
	waveOutPrepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR));//准备一个波形数据块用于播放
	waveOutWrite(hWaveOut, &waveHeader, sizeof(WAVEHDR));//在音频媒体中播放第二个参数指定的数据，也相当于开启一个播放区的意
	waveOutPrepareHeader(hWaveOut, &waveHeader2, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &waveHeader2, sizeof(WAVEHDR));
	while (waveHeader.dwBufferLength != 0 || waveHeader2.dwBufferLength != 0){
		Sleep(500);
	}
	working = false;
	resetEnergy();
	waveOutUnprepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR));//清理数据
	waveOutUnprepareHeader(hWaveOut, &waveHeader2, sizeof(WAVEHDR));
	delete []waveHeader.lpData;
	delete []waveHeader2.lpData;
	waveOutReset(hWaveOut);
	waveOutClose(hWaveOut);
	PCMstream.release();
	playing = false;
	resetEnergy();
	return 0U;
}
dword PCMdevice::play(const audio &ad){
	audio ad1 = ad;
	stream sPCMstream;
	ad1.make2(sPCMstream);
	play(sPCMstream);
	return 0U;
}
void CALLBACK PCMdevice::callBackFuncO(HWAVEOUT hwo, dword uMsg, void* ins, void* para1, void* para2){
	if(WOM_DONE == uMsg){
		LPWAVEHDR pWaveHeader = (LPWAVEHDR)para1;
		PCMdevice *context = (PCMdevice*)ins;
		stream *pPCMstream = &(context->PCMstream);
		if(pPCMstream->getPosition() + MAXSIZE > pPCMstream->length){
			pWaveHeader->dwBufferLength = pPCMstream->length - pPCMstream->getPosition();
			pPCMstream->read(pWaveHeader->lpData, pWaveHeader->dwBufferLength);
			context->updateEnergy(pWaveHeader);
		}else{
			pWaveHeader->dwBufferLength = MAXSIZE;
			pPCMstream->read(pWaveHeader->lpData, MAXSIZE);
			context->updateEnergy(pWaveHeader);
		}
		if(pWaveHeader->dwBufferLength > 0){
			waveOutPrepareHeader(hwo, pWaveHeader, sizeof(WAVEHDR));
			waveOutWrite(hwo, pWaveHeader, sizeof(WAVEHDR));
		}
	}
}
dword PCMdevice::record(){
	recording = true;
	resetEnergy();
	MMRESULT r = waveInOpen(&hWaveIn, WAVE_MAPPER, &waveFormat,(DWORD_PTR)callBackFuncI, (DWORD_PTR)this, CALLBACK_FUNCTION);
	if(MMSYSERR_NOERROR != r){
		recording = false;
		return 0U;
	}
	PCMstream.allocate(1);
	waveHeader.lpData = new char[MAXSIZE];
	waveHeader.dwBufferLength = MAXSIZE;
	waveHeader.dwLoops = 1L;
	waveHeader.dwBytesRecorded = 0L;
	waveHeader.dwUser = 0L;
	waveHeader.dwFlags = 0L;
	waveHeader2.lpData = new char[MAXSIZE];
	waveHeader2.dwBufferLength = MAXSIZE;
	waveHeader2.dwLoops = 1L;
	waveHeader2.dwBytesRecorded = 0L;
	waveHeader2.dwUser = 0L;
	waveHeader2.dwFlags = 0L;
	working = true;
	resetEnergy();
	waveInPrepareHeader(hWaveIn, &waveHeader, sizeof(WAVEHDR));
	waveInAddBuffer(hWaveIn, &waveHeader, sizeof (WAVEHDR));
	waveInPrepareHeader(hWaveIn, &waveHeader2, sizeof(WAVEHDR));
	waveInAddBuffer(hWaveIn, &waveHeader2, sizeof (WAVEHDR));
	waveInStart(hWaveIn);
	return 1U;
}
void CALLBACK PCMdevice::callBackFuncI(HWAVEIN hwi, dword uMsg, void*ins, void* para1, void*para2){
	if(WIM_DATA == uMsg){
		LPWAVEHDR pWaveHeader = (LPWAVEHDR)para1;
		PCMdevice *context = (PCMdevice*)ins;
		stream *pPCMstream = &(context->PCMstream);
		Sleep(10);
		//printf("%d %d\n", pWaveHeader->dwBytesRecorded, pWaveHeader->dwBufferLength);
		if(pWaveHeader->lpData){
			pPCMstream->push(pWaveHeader->lpData, pWaveHeader->dwBufferLength);
			context->updateEnergy(pWaveHeader);
		}
		if(context->working){
			waveInAddBuffer(hwi, pWaveHeader, sizeof(WAVEHDR));
		}
	}
}

void PCMdevice::stop(){
	if(playing){
		PCMstream.setPosition(PCMstream.length);
	}else if(recording){
		waveInUnprepareHeader(hWaveIn, &waveHeader, sizeof (WAVEHDR));
		waveInUnprepareHeader(hWaveIn, &waveHeader2, sizeof (WAVEHDR));
		working = false;
		resetEnergy();
		waveInStop(hWaveIn);
		waveInReset(hWaveIn);	
		waveInClose(hWaveIn);
		delete []waveHeader.lpData;
		delete []waveHeader2.lpData;
		waveHeader2.lpData = NULL;
		waveHeader.lpData = NULL;
		recording = false;
		resetEnergy();
	}
}
bool PCMdevice::getData(stream &cPCMstream){
	cPCMstream = PCMstream;
	return cPCMstream.length > 0;
}
longex PCMdevice::getPos(){
	if(!working)
		return 0;
	MMTIME T;
	if(playing){
		waveOutGetPosition(hWaveOut, &T, sizeof(MMTIME));
	}else if(recording){
		waveInGetPosition(hWaveIn, &T, sizeof(MMTIME));
	}
	return T.u.sample/waveFormat.nBlockAlign;
}
PCMplayer::PCMplayer(){
	idv = -1;
}
PCMplayer::PCMplayer(void*cp){
	context = cp;
	idv = -1;
}
void PCMplayer::play(const audio &ad){
	int freeID = -1;
	for(int i = 0;i<countDevice;i++)
		if(!dv[i].playing)
			freeID = i;
	idv = freeID;
	if(freeID == -1)
		return;
	audio au = ad;
	au.doubleChannel();
	dv[freeID].initFormat(2, 16, au.sampleRate, au.sampleRate*2, 4, 0);
	dv[freeID].play(au);
	
}
void PCMplayer::stop(){
	for(int i = 0;i<countDevice;i++)
		dv[i].stop();
}
longex PCMplayer::position(){
	if(idv == -1)
		return 0;
	return dv[idv].getPos();
}

KoishiAudioTool::OGGvorbis::OGGencodeSetting::OGGencodeSetting(char newBrMode, char newBr, double newQuality) {
	br = newBr;
	quality = newQuality;
	brMode = newBrMode;
}
KoishiAudioTool::OGGvorbis::OGGobject::OGGobject() {
	version = 0;
	channels = 0;
	sampleRate = 0;
	bitrateMax = -1;
	bitrateMin = -1;
	bitrateNormal = -1;
}
//Libvorbis上的解码
bool KoishiAudioTool::OGGvorbis::OGGobject::decode(stream &source) {
	source.movePosition(0);
	rawData.release();
	rawData.allocate(source.length + 1);
	comment.clearInfo();
	ogg_int16_t convbuffer[4096]; /* take 8k out of the data segment, not the stack */
	int convsize = 4096;
	ogg_sync_state   oy; /* sync and verify incoming physical bitstream */
	ogg_stream_state os; /* take physical pages, weld into a logical stream of packets */
	ogg_page         og; /* one Ogg bitstream page. Vorbis packets are inside */
	ogg_packet       op; /* one raw packet of data for decode */
	vorbis_info      vi; /* struct that stores all the static vorbis bitstream settings */
	vorbis_comment   vc; /* struct that stores all the bitstream user comments */
	vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
	vorbis_block     vb; /* local working space for packet->PCM decode */
	char *buffer;
	int  bytes;
	/********** Decode setup ************/
	ogg_sync_init(&oy); /* Now we can read pages */
	while(1) { /* we repeat if the bitstream is chained */
		int eos = 0;
		int i;
		/* grab some data at the head of the stream. We want the first page
		(which is guaranteed to be small and only contain the Vorbis
		stream initial header) We need the first page to get the stream
		serialno. */
		/* submit a 4k block to libvorbis' Ogg layer */
		buffer = ogg_sync_buffer(&oy, 4096);
		bytes = source.read(buffer, 4096);
		ogg_sync_wrote(&oy, bytes);
		/* Get the first page. */
		if(ogg_sync_pageout(&oy, &og) != 1) {
			/* have we simply run out of data?  If so, we're done. */
			if(bytes<4096)break;
			/* error case.  Must not be Vorbis data */
			errorMessage = "Input does not appear to be an Ogg bitstream.";
			return false;
		}

		/* Get the serial number and set up the rest of decode. */
		/* serialno first; use it to set up a logical stream */
		ogg_stream_init(&os, ogg_page_serialno(&og));

		/* extract the initial header from the first page and verify that the
		Ogg bitstream is in fact Vorbis data */

		/* I handle the initial header first instead of just having the code
		read all three Vorbis headers at once because reading the initial
		header is an easy way to identify a Vorbis bitstream and it's
		useful to see that functionality seperated out. */

		vorbis_info_init(&vi);
		vorbis_comment_init(&vc);
		if(ogg_stream_pagein(&os, &og)<0) {
			/* error; stream version mismatch perhaps */
			errorMessage = "Error reading first page of Ogg bitstream data.";
			return false;
		}

		if(ogg_stream_packetout(&os, &op) != 1) {
			/* no page? must not be vorbis */
			errorMessage= "Error reading initial header packet.";
			return false;
		}

		if(vorbis_synthesis_headerin(&vi, &vc, &op)<0) {
			/* error case; not a vorbis header */
			errorMessage = "This Ogg bitstream does not contain Vorbis audio data.";
			return false;
		}

		/* At this point, we're sure we're Vorbis. We've set up the logical
		(Ogg) bitstream decoder. Get the comment and codebook headers and
		set up the Vorbis decoder */

		/* The next two packets in order are the comment and codebook headers.
		They're likely large and may span multiple pages. Thus we read
		and submit data until we get our two packets, watching that no
		pages are missing. If a page is missing, error out; losing a
		header page is the only place where missing data is fatal. */

		i = 0;
		while(i<2) {
			while(i<2) {
				int result = ogg_sync_pageout(&oy, &og);
				if(result == 0)break; /* Need more data */
				/* Don't complain about missing or corrupt data yet. We'll
				catch it at the packet output phase */
				if(result == 1) {
					ogg_stream_pagein(&os, &og); /* we can ignore any errors here
												 as they'll also become apparent
												 at packetout */
					while(i<2) {
						result = ogg_stream_packetout(&os, &op);
						if(result == 0)break;
						if(result<0) {
							/* Uh oh; data at some point was corrupted or missing!
							We can't tolerate that in a header.  Die. */
							errorMessage = "Corrupt secondary header.";
							return false;
						}
						result = vorbis_synthesis_headerin(&vi, &vc, &op);
						if(result<0) {
							errorMessage = "Corrupt secondary header.";
							return false;
						}
						i++;
					}
				}
			}
			/* no harm in not checking before adding more */
			buffer = ogg_sync_buffer(&oy, 4096);
			bytes = source.read(buffer, 4096);
			if(bytes == 0 && i<2) {
				errorMessage = "End of file before finding all Vorbis headers!";
				return false;
			}
			ogg_sync_wrote(&oy, bytes);
		}
		//填充信息数据
		version = vi.version;
		channels = vi.channels;
		sampleRate = vi.rate;
		bitrateMin = vi.bitrate_lower;
		bitrateMax = vi.bitrate_upper;
		bitrateNormal = vi.bitrate_nominal;
		comment.vendorInfo = str(vc.vendor);
		for(int i = 0; i < vc.comments; i++) {
			comment.userInfo.push_back(str(vc.user_comments[i]));
		}
		//开始解码
		convsize = 4096 / vi.channels;

		/* OK, got and parsed all three headers. Initialize the Vorbis
		packet->PCM decoder. */
		if(vorbis_synthesis_init(&vd, &vi) == 0) { /* central decode state */
			vorbis_block_init(&vd, &vb);          /* local state for most of the decode
												  so multiple block decodes can
												  proceed in parallel. We could init
												  multiple vorbis_block structures
												  for vd here */

			/* The rest is just a straight decode loop until end of stream */
			while(!eos) {
				while(!eos) {
					int result = ogg_sync_pageout(&oy, &og);
					if(result == 0)break; /* need more data */
					if(result<0) { /* missing or corrupt data at this page position */
						printf("Corrupt or missing data in bitstream; "
							   "continuing...\n");
					} else {
						ogg_stream_pagein(&os, &og); /* can safely ignore errors at
													 this point */
						while(1) {
							result = ogg_stream_packetout(&os, &op);

							if(result == 0)break; /* need more data */
							if(result<0) { /* missing or corrupt data at this page position */
								/* no reason to complain; already complained above */
							} else {
								/* we have a packet.  Decode it */
								float **pcm;
								int samples;

								if(vorbis_synthesis(&vb, &op) == 0) /* test for success! */
									vorbis_synthesis_blockin(&vd, &vb);
								/*

								**pcm is a multichannel float vector.  In stereo, for
								example, pcm[0] is left, and pcm[1] is right.  samples is
								the size of each channel.  Convert the float values
								(-1.<=range<=1.) to whatever PCM format and write it out */

								while((samples = vorbis_synthesis_pcmout(&vd, &pcm))>0) {
									int j;
									int clipflag = 0;
									int bout = (samples<convsize ? samples : convsize);
									/* convert floats to 16 bit signed ints (host order) and
									interleave */
									for(i = 0; i<vi.channels; i++) {
										ogg_int16_t *ptr = convbuffer + i;
										float  *mono = pcm[i];
										for(j = 0; j<bout; j++) {
											int val = floor(mono[j] * 32767.f + .5f);
											/* might as well guard against clipping */
											if(val>32767) {
												val = 32767;
												clipflag = 1;
											}
											if(val<-32768) {
												val = -32768;
												clipflag = 1;
											}
											*ptr = val;
											ptr += vi.channels;
										}
									}
									rawData.push(convbuffer, 2 * vi.channels * bout);
									vorbis_synthesis_read(&vd, bout);
								}
							}
						}
						if(ogg_page_eos(&og))eos = 1;
					}
				}
				if(!eos) {
					buffer = ogg_sync_buffer(&oy, 4096);
					bytes = source.read(buffer, 4096);
					ogg_sync_wrote(&oy, bytes);
					if(bytes == 0)eos = 1;
				}
			}
			/* ogg_page and ogg_packet structs always point to storage in
			libvorbis.  They're never freed or manipulated directly */
			vorbis_block_clear(&vb);
			vorbis_dsp_clear(&vd);
		} else {
			errorMessage = "Error: Corrupt header during playback initialization.";
			return false;
		}
		/* clean up this logical bitstream; before exit we see if we're
		followed by another [chained] */
		ogg_stream_clear(&os);
		vorbis_comment_clear(&vc);
		vorbis_info_clear(&vi);  /* must be called last */
	}
	/* OK, clean up the framer */
	ogg_sync_clear(&oy);
	errorMessage = "解码完成";
	return true;
}
//Libvorbis上的编码
bool KoishiAudioTool::OGGvorbis::OGGobject::encode(stream &dest, const OGGencodeSetting &setting) {
	if(rawData.length == 0)
		return false;
	if(channels != 1 && channels != 2)
		return false;
	rawData.setPosition(0);
	dest.release();
	dest.allocate(rawData.length);
	const unsigned READ = 1024;
	signed char readbuffer[READ * 4 + 44]; /* out of the data segment, not the stack */
	ogg_stream_state os; /* take physical pages, weld into a logical 						 stream of packets */
	ogg_page         og; /* one Ogg bitstream page.  Vorbis packets are inside */
	ogg_packet       op; /* one raw packet of data for decode */
	vorbis_info      vi; /* struct that stores all the static vorbis bitstream
						 settings */
	vorbis_comment   vc; /* struct that stores all the user comments */
	vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
	vorbis_block     vb; /* local working space for packet->PCM decode */

	int eos = 0;
	int i;

	/********** Encode setup ************/
	vorbis_info_init(&vi);
	int ret = 0;
	switch(setting.brMode) {
	case 'A':
		ret = vorbis_encode_init(&vi, channels, sampleRate, -1, setting.br, -1);
		break;
	case 'C':
		ret = vorbis_encode_init(&vi, channels, sampleRate, setting.br, setting.br, setting.br);
		break;
	default:
		//i.e case 'V':
		ret = vorbis_encode_init_vbr(&vi, channels, sampleRate, setting.quality);
		break;
	}
	if(0 != ret) {
		errorMessage = "编码器参数设置错误";
		return false;
	}

	/* add comments */
	vorbis_comment_init(&vc);
	for(i = 0; i < comment.userInfo.size(); i++)
		vorbis_comment_add(&vc, comment.userInfo[i].c_str());

	/* set up the analysis state and auxiliary encoding storage */
	vorbis_analysis_init(&vd, &vi);
	vorbis_block_init(&vd, &vb);

	/* set up our packet->stream encoder */
	/* pick a random serial number; that way we can more likely build
	chained streams just by concatenation */
	srand(514/*time(NULL)*/);
	ogg_stream_init(&os, rand());

	/* Vorbis streams begin with three headers; the initial header (with
	most of the codec setup parameters) which is mandated by the Ogg
	bitstream spec.  The second header holds any comment fields.  The
	third header holds the bitstream codebook.  We merely need to
	make the headers, then pass them to libvorbis one at a time;
	libvorbis handles the additional Ogg bitstream constraints */

	if(true/*写入头*/) {
		ogg_packet header;
		ogg_packet header_comm;
		ogg_packet header_code;

		vorbis_analysis_headerout(&vd, &vc, &header, &header_comm, &header_code);
		ogg_stream_packetin(&os, &header); /* automatically placed in its own
										   page */
		ogg_stream_packetin(&os, &header_comm);
		ogg_stream_packetin(&os, &header_code);

		/* This ensures the actual
		* audio data will start on a new page, as per spec
		*/
		while(!eos) {
			int result = ogg_stream_flush(&os, &og);
			if(result == 0)
				break;
			dest.push(og.header, og.header_len);
			dest.push(og.body, og.body_len);
		}
		bitrateMax = vi.bitrate_upper;
		bitrateNormal = vi.bitrate_nominal;
		bitrateMin = vi.bitrate_lower;
		version = vi.version;
		comment.userInfo.clear();
		for(int i = 0; i < vc.comments; i++) {
			comment.userInfo.push_back(str(vc.user_comments[i]));
		}
	}
	while(!eos) {
		long i;
		long bytes = rawData.read(readbuffer, READ * 4);
		if(bytes == 0) {
			/* end of file.  this can be done implicitly in the mainline,
			but it's easier to see here in non-clever fashion.
			Tell the library we're at end of stream so that it can handle
			the last frame and mark end of stream in the output properly */
			vorbis_analysis_wrote(&vd, 0);

		} else {
			/* data to encode */

			/* expose the buffer to submit data */
			float **buffer = vorbis_analysis_buffer(&vd, READ);

			/* uninterleave samples */
			if(channels == 2) {
				for(i = 0; i<bytes / 4; i++) {
					buffer[0][i] = ((readbuffer[i * 4 + 1] << 8) |
									(0x00ff & (int)readbuffer[i * 4])) / 32768.f;
					buffer[1][i] = ((readbuffer[i * 4 + 3] << 8) |
									(0x00ff & (int)readbuffer[i * 4 + 2])) / 32768.f;
				}
			} else {
				for(i = 0; i<bytes / 2; i++) {
					buffer[0][i] = ((readbuffer[i * 2 + 1] << 8) |
									(0x00ff & (int)readbuffer[i * 2])) / 32768.f;
				}
			}

			/* tell the library how much we actually submitted */
			vorbis_analysis_wrote(&vd, i);
		}

		/* vorbis does some data preanalysis, then divvies up blocks for
		more involved (potentially parallel) processing.  Get a single
		block for encoding now */
		while(vorbis_analysis_blockout(&vd, &vb) == 1) {

			/* analysis, assume we want to use bitrate management */
			vorbis_analysis(&vb, NULL);
			vorbis_bitrate_addblock(&vb);

			while(vorbis_bitrate_flushpacket(&vd, &op)) {

				/* weld the packet into the bitstream */
				ogg_stream_packetin(&os, &op);

				/* write out pages (if any) */
				while(!eos) {
					int result = ogg_stream_pageout(&os, &og);
					if(result == 0)
						break;
					dest.push(og.header, og.header_len);
					dest.push(og.body, og.body_len);

					/* this could be set above, but for illustrative purposes, I do
					it here (to show that vorbis does know where the stream ends) */

					if(ogg_page_eos(&og))
						eos = 1;
				}
			}
		}
	}

	/* clean up and exit.  vorbis_info_clear() must be called last */

	ogg_stream_clear(&os);
	vorbis_block_clear(&vb);
	vorbis_dsp_clear(&vd);
	vorbis_comment_clear(&vc);
	vorbis_info_clear(&vi);

	/* ogg_page and ogg_packet structs always point to storage in
	libvorbis.  They're never freed or manipulated directly */
	errorMessage = "编码完成";
	return true;
}

bool KoishiAudioTool::OGGvorbis::OGGobject::decodeFile(const str &fileName) {
	stream source;
	if(!source.loadFile(fileName))
		return false;
	return decode(source);
}

bool KoishiAudioTool::OGGvorbis::OGGobject::makeAudio(audio &ad) {
	if(channels != 1 && channels != 2)
		return false;
	ad.destory();
	if(rawData.length == 0)
		return false;
	ad.create(rawData, channels, sampleRate);
	return true;
}
bool KoishiAudioTool::OGGvorbis::OGGobject::decodeAndMake(stream &source, audio &ad) {
	if(!decode(source))
		return false;
	if(!makeAudio(ad))
		return false;
	return true;
}
bool KoishiAudioTool::OGGvorbis::OGGobject::decodeFileAndMake(const str &fileName, audio &ad) {
	stream source;
	if(!source.loadFile(fileName))
		return false;
	return decodeAndMake(source, ad);
}
bool KoishiAudioTool::OGGvorbis::OGGobject::loadAudio(const audio &ad) {
	if(ad.channel != 1 && ad.channel != 2)
		return false;
	if(ad.length == 0)
		return false;
	//将AD重置为2声道
	rawData.release();
	rawData.allocate(ad.length * 4 + 10);
	channels = 2;
	sampleRate = ad.sampleRate;
	version = 0;
	bitrateMax = -1;
	bitrateMin = -1;
	bitrateNormal = -1;
	if(ad.channel == 2) {
		rawData.push(ad.begin(0), ad.length << 2);
	} else for(int i = 0; i < ad.length; i++) {
		short samp = ad[i][0];
		rawData.push(&samp, 2);
		rawData.push(&samp, 2);
	}
	return true;
}

bool KoishiAudioTool::OGGvorbis::OGGobject::encodeToFile(const str &fileName, const OGGencodeSetting &setting) {
	stream dest;
	if(!encode(dest, setting))
		return false;
	if(!dest.makeFile(fileName))
		return false;
	return true;
}


bool KoishiAudioTool::OGGvorbis::OGGobject::loadAndEncode(const audio &ad, stream &dest, const OGGencodeSetting &setting) {
	if(!loadAudio(ad))
		return false;
	if(!encode(dest, setting))
		return false;
	return true;
}
bool KoishiAudioTool::OGGvorbis::OGGobject::loadAndEncodeToFile(const audio &ad, const str &fileName, const OGGencodeSetting &setting) {
	stream dest;
	if(!loadAndEncode(ad, dest, setting))
		return false;
	if(!dest.makeFile(fileName))
		return false;
	return true;
}

bool KoishiAudioTool::OGGvorbis::OGGcomment::addInfo(const str &key, const str &value) {
	userInfo.push_back(key + "=" + value);
	return true;
}
bool KoishiAudioTool::OGGvorbis::OGGcomment::clearInfo() {
	userInfo.clear();
	return true;
}
str KoishiAudioTool::OGGvorbis::OGGcomment::getKeyInfo(int kID) {
	if(kID < 0 || kID >= userInfo.size())
		return "";
	str nStr = userInfo[kID];
	str::size_type st = nStr.find_first_of('=');
	if(st == 0 || st == str::npos)
		return "";
	return nStr.substr(0, st);
}
str KoishiAudioTool::OGGvorbis::OGGcomment::getValueInfo(int kID) {
	if(kID < 0 || kID >= userInfo.size())
		return "";
	str nStr = userInfo[kID];
	str::size_type st = nStr.find_first_of('=');
	if(st == nStr.size() - 1 || st == str::npos)
		return "";
	return nStr.substr(st+1);
}
int KoishiAudioTool::OGGvorbis::OGGcomment::queryInfo(const str &key, int startPos) {
	for(int i = startPos; i < userInfo.size(); i++) {
		if(getKeyInfo(i) == key) {
			return i;
		}
	}
	return -1;
}
int KoishiAudioTool::OGGvorbis::OGGcomment::queryLastInfo(const str &key) {
	for(int i = userInfo.size() - 1; i >= 0; i--) {
		if(getKeyInfo(i) == key) {
			return i;
		}
	}
	return -1;
}
bool KoishiAudioTool::OGGvorbis::OGGcomment::modifyInfo(const str &key, const str &value) {
	for(int i = 0; i < userInfo.size(); i++) {
		if(getKeyInfo(i) == key) {
			userInfo[i] = key + "=" + value;
			return true;
		}
	}
	addInfo(key, value);
	return false;
}
bool KoishiAudioTool::OGGvorbis::OGGcomment::modifyLastInfo(const str &key, const str &value) {
	for(int i = userInfo.size() - 1; i >= 0; i--) {
		if(getKeyInfo(i) == key) {
			userInfo[i] = key + "=" + value;
			return true;
		}
	}
	addInfo(key, value);
	return false;
}
bool KoishiAudioTool::OGGvorbis::OGGcomment::addInfo_author(const str &author, const str &localTime) {
	addInfo("artist", author);
	addInfo("created_date", localTime);
	addInfo("soft", "Koishi's EX Whitecat Version");
	return true;
}
bool KoishiAudioTool::OGGvorbis::OGGcomment::addInfo_modifier(const str &modifier, const str &localTime) {
	int kID = queryLastInfo("modifier");
	if(queryLastInfo("artist") != -1 && kID == -1) {
		//有原作者但没有修改痕迹
		modifyLastInfo("created_date", localTime);
		return true;
	}
	if(kID == -1) {
		addInfo("modifier", modifier);
		addInfo("modified_date", localTime);
		return true;
	}
	if(getValueInfo(kID) == modifier) {
		modifyLastInfo("modified_date", localTime);
		return true;
	}
	addInfo("modifier", modifier);
	addInfo("modified_date", localTime);
	return true;
}
