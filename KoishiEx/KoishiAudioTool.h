#include "stdafx.h"
#include "KoishiEx.h"
#include "windows.h"
#include "KoishiNeoplePack.h"
#include <MMSystem.h>
#include <math.h>

#pragma once
using namespace Koishi;

namespace KoishiAudioTool{
	//���򵥵Ŀ��ٸ���Ҷ�任,inv = trueΪ�渵��Ҷ�任���ڶ�������ʵ����
	static void FFT(complex*a, int n);
	static void FFT(double*a, int n);
	//���Ʋ���ͼ
	extern void makeWaveGraph(const audio &ad, int channels, image &mat, int width, int height);
	extern void makeWaveGraphDB(const audio &ad, int channels, image &mat, int width, int height);
	//�򵥵��б���Ƶ�ļ��ķ�ʽ
	KoishiNeoplePack::SNDversion checkAudioFormat(stream &sour);
	//��Ƶ�豸����������PCM����
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
		PCMdevice dv[countDevice];	//�豸����		 
		int idv;					//���һ���������豸
		void *context;				//������
	public:
		void play(const audio &ad);	//ָ��һ�������豸���в��ţ�������������˾��޷�������
		void stop();				//ֹͣ�����豸
		longex position();			//������һ���������豸������λ��
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
			word audioFormat;	//1ΪPCM��������Ϊ��ʽ������ѹ����ʽ
			word channels;
			long sampleRate;	//����Ƶ�� ��λ��HZ
			long byteRate;		//��λ B/s
			word byteAlign;		//ÿ���������ֽ���
			word bitPerSample;	//ÿ��������λ����8����16
			long extraInfo;		//�ܲ�������audioFormat��Ϊ1ʱ��Ч
			stream rawData;		//ԭʼ����
		public:
			bool decode(stream &source);
			bool decodeFile(const str &fileName);
			bool encode(stream &dest);
			bool encodeToFile(const str &fileName);
		public:
			bool makeAudio(audio &ad);	//����audio
			bool decodeAndMake(stream &source, audio &ad);
			bool decodeFileAndMake(const str &fileName, audio &ad);
			bool loadAudio(const audio &ad);
			bool loadAndEncode(const audio &ad, stream &dest);
			bool loadAndEncodeToFile(const audio &ad, const str &fileName);
		};
	}
	//��libvorbis��libogg�����
	namespace OGGvorbis {
		//OGG������������
		class OGGencodeSetting {
		public:
			OGGencodeSetting(char newBrMode, char newBr, double newQuality);
			char brMode;		//XBRģʽ	X����Ϊ"V","C","A"���ֱ�Ϊ�ɱ�����ʡ����������ʡ�����Ӧ������
			long br;			//������	CBR��ABR��Ч
			double quality;		//Ʒ��		VBR��Ч��-0.1��1.0�����⸡����
		};
		class OGGcomment {
		public:
			str vendorInfo;
			std::vector<str> userInfo;
		public:
			//COMMENT�Ĳ���
			bool addInfo(const str &key, const str &value);		//׷��ֵ
			bool clearInfo();
			str getKeyInfo(int kID);
			str getValueInfo(int kID);
			int queryInfo(const str &key, int startPos = 0);	//��ѯ��ֵ������λ�ã��鲻������-1
			int queryLastInfo(const str &key);					//��ѯ���һ��ͬ���ļ�ֵ
			bool modifyInfo(const str &key, const str &value);	//�޸�ֵ������鲻����׷��ֵ
			bool modifyLastInfo(const str &key, const str &value);	//�޸�ֵ������鲻����׷��ֵ
		public:
			//����ʱ������addInfo_author�����author��create_time��tool��ֵ
			bool addInfo_author(const str &author, const str &localTime);
		public:
			//�޸�ʱ������addInfo_modifier�����modifier��modified_time��ֵ
			//����޸��������һ��modifier��ֵ��ͬ������ӣ�ֱ���޸����һ��modified��ֵ
			//���û�з���tool��ֵ���߱���tool��ֵ��ʱ����֮ǰ��ͬ�������һ��tool��ֵ
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
			stream rawData;			//ԭʼ������
			str errorMessage;		//�����������Ϣ
		public:
			//���룬����decode֮ǰ�������ͷ���Դ�����Ѿ��������
			bool decode(stream &source);					//��OGG�������ж�ȡ��Ϣ���������룩
			bool decodeFile(const str &fileName);			//���ⲿOGG�ļ��ж�ȡ��Ϣ
			bool makeAudio(audio &ad);						//����������audio��Դ
			bool decodeAndMake(stream &source, audio &ad);	//����������ȡ��������audio��Դ
			bool decodeFileAndMake(const str &fileName, audio &ad);
		public:
			bool loadAudio(const audio &ad);
			//���롤��Ϊ������û��ͨ��������ad��ʱ��ǿ��ת��Ϊ2ʡ��
			//������ҪԤ�����ú�channels��sampleRate��rawData��comment����
			//ǰ��������ͨ������loadAudio()ʵ��
			bool encode(stream &dest, const OGGencodeSetting &setting = OGGencodeSetting('V', -1, .4));
			bool encodeToFile(const str &fileName, const OGGencodeSetting &setting = OGGencodeSetting('V', -1, .4));
			bool loadAndEncode(const audio &ad, stream &dest, const OGGencodeSetting &setting = OGGencodeSetting('V', -1, .4));
			bool loadAndEncodeToFile(const audio &ad, const str &fileName, const OGGencodeSetting &setting = OGGencodeSetting('V', -1, .4));
		};
	}
}