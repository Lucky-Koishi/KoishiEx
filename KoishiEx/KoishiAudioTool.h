#include "stdafx.h"
#include "KoishiEx.h"
#include "windows.h"
#include "KoishiNeoplePack.h"
#include <MMSystem.h>
#include <math.h>

#pragma once
using namespace Koishi;

namespace KoishiAudioTool{
	//极简单的快速傅里叶变换,inv = true为逆傅里叶变换，第二个返回实部长
	static void FFT(complex*a, int n);
	static void FFT(double*a, int n);
	//绘制波形图
	extern void makeWaveGraph(const audio &ad, int channels, image &mat, int width, int height);
	extern void makeWaveGraphDB(const audio &ad, int channels, image &mat, int width, int height);
	//简单的判别音频文件的方式
	KoishiNeoplePack::SNDversion checkAudioFormat(stream &sour);
	//音频设备，用来播放PCM裸流
	class PCMdevice{
	private:
		static const dword MAXSIZE = 0x2000;
		static void CALLBACK callBackFuncO(HWAVEOUT hwo, dword uMsg, void*ins, void* para1, void*para2);
		static void CALLBACK callBackFuncI(HWAVEIN hwi, dword uMsg, void*ins, void* para1, void*para2);
		HWAVEIN hWaveIn;
		HWAVEOUT hWaveOut;
		WAVEHDR waveHeader, waveHeader2;
		WAVEFORMATEX waveFormat;
		stream PCMstream;
	public:
		PCMdevice();
		volatile bool playing;
		volatile bool working;
		volatile bool recording;
		volatile short energyLeft;
		volatile short energyRight;
		volatile double freq[16];
		void initFormat(int channels, int bitPerSample, int sampleRate, int byteRate, int byteAlign, int cbSize);
		//bool initFormat(const WAV::WAVobject &PCMwavObject);
		dword play(const stream &cPCMstream);
		dword play(const audio &ad);
		dword record();
		void stop();
		bool getData(stream &cPCMstream);
		longex getPos();
		void resetEnergy();
		void updateEnergy(LPWAVEHDR lpWaveHeader);
	};
	class PCMplayer{
	public:
		static const int countDevice = 16;
		PCMplayer();
		PCMplayer(void*);
		PCMdevice dv[countDevice];	//设备阵列		 
		int idv;					//最后一次启动的设备
		void *context;				//上下文
	public:
		void play(const audio &ad);	//指定一个空闲设备进行播放，如果播放器满了就无法播放了
		void stop();				//停止所有设备
		longex position();			//获得最后一次启动的设备内流的位置
	};
	namespace WAV {
		typedef struct WAVinfo {
			char magic[5];
			dword size;
			char type[5];
		}WAVinfo;
		typedef struct WAVchunk {
			char magic[5];
			dword size;
			stream data;
		}WAVchunk;
		class WAVobject {
		private:
			WAVinfo info;
			std::vector<WAVchunk> chunk;
		public:
			word audioFormat;	//1为PCM，其他则为各式各样的压缩方式
			word channels;
			long sampleRate;	//采样频率 单位：HZ
			long byteRate;		//单位 B/s
			word byteAlign;		//每个采样的字节数
			word bitPerSample;	//每个采样的位数（8或者16
			long extraInfo;		//总采样数，audioFormat不为1时有效
			stream rawData;		//原始数据
		public:
			bool decode(stream &source);
			bool decodeFile(const str &fileName);
			bool encode(stream &dest);
			bool encodeToFile(const str &fileName);
		public:
			bool makeAudio(audio &ad);	//生成audio
			bool decodeAndMake(stream &source, audio &ad);
			bool decodeFileAndMake(const str &fileName, audio &ad);
			bool loadAudio(const audio &ad);
			bool loadAndEncode(const audio &ad, stream &dest);
			bool loadAndEncodeToFile(const audio &ad, const str &fileName);
		};
	}
	//从libvorbis和libogg库调用
	namespace OGGvorbis {
		//OGG编码器的设置
		class OGGencodeSetting {
		public:
			OGGencodeSetting(char newBrMode, char newBr, double newQuality);
			char brMode;		//XBR模式	X可以为"V","C","A"，分别为可变比特率、常数比特率、自适应比特率
			long br;			//比特率	CBR、ABR有效
			double quality;		//品质		VBR有效，-0.1到1.0的任意浮点数
		};
		class OGGcomment {
		public:
			str vendorInfo;
			std::vector<str> userInfo;
		public:
			//COMMENT的操作
			bool addInfo(const str &key, const str &value);		//追加值
			bool clearInfo();
			str getKeyInfo(int kID);
			str getValueInfo(int kID);
			int queryInfo(const str &key, int startPos = 0);	//查询键值，返回位置，查不到返回-1
			int queryLastInfo(const str &key);					//查询最后一个同名的键值
			bool modifyInfo(const str &key, const str &value);	//修改值，如果查不到则追加值
			bool modifyLastInfo(const str &key, const str &value);	//修改值，如果查不到则追加值
		public:
			//创建时，调用addInfo_author，添加author、create_time、tool键值
			bool addInfo_author(const str &author, const str &localTime);
		public:
			//修改时，调用addInfo_modifier，添加modifier、modified_time键值
			//如果修改者与最后一个modifier键值相同，则不添加，直接修改最后一个modified的值
			//如果没有发现tool键值或者保存tool键值的时候与之前不同，则添加一个tool键值
			bool addInfo_modifier(const str &modifier, const str &localTime);
		};
		class OGGobject {
		public:
			OGGobject();
		public:
			int version;
			int channels;
			int sampleRate;
			int bitrateMax;
			int bitrateMin;
			int bitrateNormal;
		public:
			OGGcomment comment;
			stream rawData;			//原始数据流
			str errorMessage;		//编解码器的消息
		public:
			//解码，调用decode之前不用现释放资源，都已经处理好了
			bool decode(stream &source);					//从OGG数据流中读取信息（包括解码）
			bool decodeFile(const str &fileName);			//从外部OGG文件中读取信息
			bool makeAudio(audio &ad);						//将其制作成audio资源
			bool decodeAndMake(stream &source, audio &ad);	//从数据流读取并制作成audio资源
			bool decodeFileAndMake(const str &fileName, audio &ad);
		public:
			bool loadAudio(const audio &ad);
			//编码·因为单声道没有通过，接收ad的时候强行转换为2省道
			//编码需要预先设置好channels、sampleRate、rawData和comment数据
			//前三个可以通过调用loadAudio()实现
			bool encode(stream &dest, const OGGencodeSetting &setting = OGGencodeSetting('V', -1, .4));
			bool encodeToFile(const str &fileName, const OGGencodeSetting &setting = OGGencodeSetting('V', -1, .4));
			bool loadAndEncode(const audio &ad, stream &dest, const OGGencodeSetting &setting = OGGencodeSetting('V', -1, .4));
			bool loadAndEncodeToFile(const audio &ad, const str &fileName, const OGGencodeSetting &setting = OGGencodeSetting('V', -1, .4));
		};
	}
}