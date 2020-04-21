#include "stdafx.h"
#include "KoishiEx.h"
#include "windows.h"
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
	namespace WAV{
		typedef struct WAVinfo{
			char magic[5];
			dword size;
			char type[5];
		}WAVinfo;
		typedef struct WAVchunk{
			char magic[5];
			dword size;
			stream data;
		}WAVchunk;
		class WAVobject{
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
			bool load(stream &s);
			bool loadFile(const str &fileName);
			bool make(stream &s);
		};
	}
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
		bool initFormat(const WAV::WAVobject &PCMwavObject);
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

	//////////////////////////////////////////////////////////////
	//OGG�����
	//////////////////////////////////////////////////////////////
	namespace OGG{
		bool OGGeasyDecode(const str &fileName, stream &pcmOut, volatile double &complete);
		bool OGGeasyDecodeAndPlay(const str &fileName);
		/////////////////////////////////////////////
		//��������
		/////////////////////////////////////////////
		namespace OGGsupport{
			inline double bit32ToFloat(dword d);
			inline int MapType1_Quantvals(int dimension, int entryCount);
			inline int ilog(int n);
			inline int lowNeighbor(queue list, int n);
			inline int highNeighbor(queue list, int n);
			inline int renderPoint(int x0, int y0, int x1, int y1, int X);
			inline void renderLine(int x0, int y0, int x1, int y1, queue &v);
			inline void renderLine(int x0, int y0, int x1, int y1, sequence &vf);
			inline double invDb(long p);
			inline queue qSort(const queue &list);
			inline queue qResort(const queue &list, const queue &indexList);
		};
		/////////////////////////////////////////////
		//��������ɢ���ұ任������libvorbis
		/////////////////////////////////////////////
		class MDCT{
		private:
			int n, log2n;
			int *bitRev;
			double *trig;
			double scale;
			static double PI;
			static double cosPI_8(int k);
			static void butterfly8(double *x);
			static void butterfly16(double *x);
			static void butterfly32(double *x);
			static void butterflyFirst(double *T, double *x, int points);
			static void butterflyGeneric(double *T, double *x, int points, int trigint);
			void butterfly(double *x,int points);
			void bitReverse(double *x);
		public:
			void initial(int n0);
			void destory();
			void backward(double *in, double *out);
			void forward(double *in, double *out);
		};
		/////////////////////////////////////////////
		//OGGҳ��
		/////////////////////////////////////////////
		typedef stream OGGpack;
		class OGGpage{
		public:
			OGGpage();
			uchar ver;
			uchar type;
			union{
				longex sampleTotalCount;
				uchar granule[8];			//��������
			};
			dword serial;					//
			dword sequence;					//ҳ�Ĵ���
			dword checkCRC;					//У����
			uchar segCount;					//�ֶ���
			std::vector<uchar> segLength;	//ÿ�ζγ�
			std::vector<stream> segData;	//������
		};
		////////////////////////////////////////
		//���뱾
		class VorbisCodeBook{
		private:
			typedef struct VorbisCodeBookEntry{
				VorbisCodeBookEntry();
				dword huffmanCode;				//����������
				long length;					//��Ŀ����
				union{
					long originID;				//��Ŀ�ڱ��뱾�е�˳��
					dword value;
				};
				long weight;					//��ĿȨ��
				char codeStr[32];				//����Ŀ������
			}Entry;								//��Ŀ
			typedef enum VorbisCodeBookMappingType:int{
				NO_LOOK_UP,						//ûӳ���
				LOOK_UP_1,						//��ʽ���ӳ���
				LOOK_UP_2						//��ʽ���ӳ��������õ���
			}MappingType;
			typedef struct VorbisCodeBookMappingPara{
				VorbisCodeBookMappingPara();
					double min;
					double delta;
				int valueBits;
				int seqP;
				int valuesCount;
				queue multiplicands;
			}MappingPara;
			typedef struct HuffmanNode{
				dword code;						//��ǰ�ڵ�Ĺ��������룬��ת��Ϊ˫��
				int depth;						//�ڵ���ȣ����ڵ�Ϊ0����ֵ���ֵΪentryLen�е����ֵ-1
				bool isLeaf;					//�Ƿ���Ҷ�ӣ�ȷ�����������²���ڵ㣬leftOK��rightOK��ΪTrue
				bool leftOK;					//��ڵ�����״���������ڵ��״̬��ȷ��������Ϊĳһ�����ڵ����ȷ��Ϊ�����ڣ���ΪҶ�ڵ�)��ΪTrue
				bool rightOK;					//�ҽڵ�����״̬
				long weight;
				HuffmanNode();
			}HuffmanNode;
		public:
			VorbisCodeBook();
			int dimension;						//���뱾��ά��
			int entryCount;						//��Ŀ��
			MappingType mappingType;			//ӳ�����ͣ�ȡֵ0-2��0�Ļ���������mapping�����Ľ�����mappingPara�ṹ��Ϊ�ա�
			int ordered;						//�����Ŀ�ĳ���������ģ����ò�ͬ�Ľ�����ʽ
			int sparsed;						//����δʹ�õ���Ŀ��δʹ�õ���Ŀ������������������
			queue entryLen;						//ÿ����Ŀ�ĳ��ȣ�����ȷ������Ŀ�Ĺ���������
			MappingPara mappingPara;			//ӳ�����ͣ�ȡֵ0-2��0�Ļ�
			bool buildFromData(stream &data);	//��һ���������н��н������������ڰ�λָ���ı�
		public:
			//��������������룬����ΪentryCount
			//�Զ����Ʊ�ʾʱ���ȶ���λ����С�ˣ�����Ϊ�Ӹ��ڵ㿪ʼ�����������10100����Ϊ00...000101B��д��0x00000005
			//ʵ�ʽ����ʱ���ڽ���ǰ�������У���λ��ȡʱ��Ҳ�ǴӸ��ڵ㿪ʼ����
			std::vector<Entry> entries;							//��ʹ�õ���Ŀ����Ȩ���ź���ģ�
			std::vector<sequence> quantized;					//�������ֵ(NO_LOOK_UP��Ч)
			bool buildTree();
			bool unquantize();
			long findEntry(long huffmanCode, long huffmanLen);	//������ţ������ҵ����򣩣��Ҳ����Ļ�������-1��
			long decodeEntryIn(stream &sour);				//��һ���������а�λ�������
			long decodeValueIn(stream &sour);				//��һ���������а�λ���ұ��룬���ظñ��������뱾����ʼλ�ã�ԭλ�ã��������ڰ�λָ���ı�
			sequence decodeVectorIn(stream &sour, int vectorLen, bool interleaved);//��һ�������������θ��ݱ��빹������ֵ���������ڰ�λָ���ı䣨��NO_LOOK_UP��Ч��
			std::vector<sequence> decodeMultVectorIn(stream &sour, int vectorLen, long offset, int ch);
		};
		////////////////////////////////////////
		//ʱ��任��VorbisI��Ϊ������;��
		class VorbisTimeDomain{
		public:
			VorbisTimeDomain();
			short reserved;
			bool buildFromData(stream &data);					//��һ���������н��н������������ڰ�λָ���ı�
		};
		////////////////////////////////////////
		//���ײ���
		class VorbisFloor{
		private:
			typedef struct VorbisFloorPartitionClass{
			public:
				VorbisFloorPartitionClass();
				dword dimension;
				dword subClasses;
				dword masterBooks;
				queue subClassBooks;
			}PartitionClass;
			typedef struct VorbisFloorFloor0{
				dword order;
				dword rate;
				dword bookMapSize;
				dword amplitudeBits;
				dword amplitudeOffset;
				dword booksCount;
				queue bookList;
			}Floor0;
			typedef struct VorbisFloorFloor1{
				dword partitions;
				queue partitionClassList;	//partitions��Ԫ��
				long maxClass;				//partitionClassList�е����ֵ
				std::vector<PartitionClass> partitionClasses;
				dword multiplier;
				dword rangeBits;
				dword values;
				queue Xlist;
			}Floor1;
		public:
			VorbisFloor();
			word floorType;
			Floor0 floor0;
			Floor1 floor1;
			bool buildFromData(stream &data);
		};
		class VorbisFloorCurve{
		public:
			VorbisFloorCurve(){
				flagNonzero = false;
				range = 0;
			}
			bool flagNonzero;
			int range;
			queue Ylist;
			queue finalYlist;
			queue step2Flag;
			queue floorCurve;
		};
		//�в����
		class VorbisResidue{
		public:
			VorbisResidue();
			word residueType;
			dword begin;
			dword end;
			dword partitionSize;
			dword classification;
			dword classBook;
			queue cascade;			//���������飬��ȡbookʹ��
			std::vector<queue> books;
			bool buildFromData(stream &data);
		public:
			dword stages;
			dword partvals;
			std::vector<queue> decodeMaps;
		};
		class VorbisMapping{
		private:
			typedef struct VorbisMappingSquarePolarChannelMappingPara{
				long magnitudes;
				long angles;
			}PolarCoordinate;
			typedef struct VorbisMappingSupmapPara{
				long discarded;
				long floor;
				long residue;
			}SubmapPara;
		public:
			VorbisMapping();
			word mappingType;
			dword submaps;
			dword couplingSteps;
			dword channels;		//�˲������ⲿ��ֵ
			std::vector<PolarCoordinate> couplingList;
			uchar reserved;
			queue mux;			//subMaps����1ʱ��Ч������Ϊͨ������
			std::vector<SubmapPara> submapList;
			bool buildFromData(stream &data);
		};
		////////////////////////////////////////
		//ģʽ����
		class VorbisMode{
		public:
			VorbisMode();
			uchar blockFlag;
			word windowType;
			word transformType;
			word mapping;
			bool buildFromData(stream &data);
		};
		////////////////////////////////////////
		//����Ϊ����������ݽṹ
		class VorbisIdentity{
		public:
			VorbisIdentity();
			dword version;
			uchar channels;
			dword sampleRate;
			long bitrateMax;
			long bitrateNorm;
			long bitrateMin;
			long blockSize0;
			long blockSize1;
		};
		class VorbisComment{
		public:
			str vendorInfo;
			std::vector<str> otherInfo;
		};
		class VorbisBlock{
		public:
			VorbisBlock();
			long serial;			//..Sequence
			long mode;				//ʹ�õ�mode
			long mapping;			//ʹ�õ�map
			long blockSize;			//���õ�blockSize
			bool flagLong;			//�����ڱ�־λ���䳤
			bool flagPrevWindow;	//ǰһ�����ڱ�־λ
			bool flagNextWindow;	//��һ�����ڱ�־λ
			std::vector<VorbisFloorCurve> floorCurve;
			std::vector<bool> floorNoResidue;
			std::vector<bool> doNotDecode;
			std::vector<sequence> residueVector;
			std::vector<sequence> spectrumVector;
			std::vector<sequence> pcmVector;
		};
		
		class OGGobject{
		public:
			std::vector<OGGpage> pages;
			std::vector<OGGpack> packs;
		public:
			std::vector<VorbisCodeBook> codeBook;
			std::vector<VorbisTimeDomain> timeDomains;
			std::vector<VorbisFloor> floors;
			std::vector<VorbisResidue> residues;
			std::vector<VorbisMapping> mappings;
			std::vector<VorbisMode> modes;
			sequence windowValueShort;		//�̴���ֵ������벿�֣����ȵ���info.blockSize0 / 2
			sequence windowValueLong;		//������ֵ������벿�֣����ȵ���info.blockSize1 / 2
			std::vector<VorbisBlock> blocks;
			std::vector<sequence> pcm;
		public:
			OGGobject();
			bool load(stream &s);
			bool loadFile(const str &fileName);					//��ȡ����
			bool initDecoder();									//��ʼ��������
			bool packDecode(int packID);						//������
			long initPCM();
			long makePCMstart();
			long makePCM(int blockID);
			long makePCMend();
			long makePCMstream(stream &s);
			void release();
		public:
			VorbisIdentity info;
			VorbisComment comment;
		};
	}
	bool loadWAV(audio &ad, const str &fileName);
	bool loadWAV(audio &ad, const stream &fileStream);
	bool loadWAV(audio &ad, const WAV::WAVobject &wo);
	bool makeWAV(const audio &ad, const str &fileName);
	bool makeWAV(const audio &ad, stream &fileStream);
	bool loadOGG(audio &ad, const str &fileName);
	bool loadOGG(audio &ad, const stream &fileStream);
	bool loadOGG(audio &ad, OGG::OGGobject &oo);

	namespace MP3{
		class MP3encoder{
		public:
			audio source;
			str author;
			str album;
			str genre;
			image pic;
		public:
			bool output(stream &outputStream);
		};
	}
	//namespace MPEG{
	//	enum MPEGversion{MPEG_2_5, MPEG_BAD, MPEG_2, MPEG_1};
	//	enum MPEGlayer{LAYER_BAD, LAYER_3, LAYER_2, LAYER_1};
	//	enum MPEGchannelMode{CHM_STEREO, CHM_JOINT_STEREO, CHM_DUAL, CHM_SINGLE};
	//	enum MPEGextenedMode{EXM_NN, EXM_YN, EXM_NY, EXM_YY};
	//	static int getBitRate(uchar bit, MPEGversion v, MPEGlayer l);
	//	static int getSampleRate(uchar bit, MPEGversion v);
	//	static int getFrameSize(int bitRate, int sampleRate, MPEGversion v, MPEGlayer l);		//ע�⣺δ����paddingλ
	//	class TagID3V1{
	//	public:
	//		bool valid;
	//		str title;
	//		str author;
	//		str album;
	//		str comment;
	//		long year;
	//		str genre;
	//		bool load(const stream &s);
	//	};
	//	class TagID3V2frame{
	//	public:
	//		str type;
	//		long length;
	//		word flag;
	//		stream data;
	//	};
	//	class TagID3V2{
	//	public:
	//		bool valid;
	//		long version;
	//		uchar flag;
	//		long length;
	//		std::vector<TagID3V2frame> frames;
	//		bool load(const stream &s);
	//	};
	//	class MPEGframe{
	//	public:
	//		//֡ͷ
	//		struct{
	//			int syncInfo;
	//			MPEGversion version;
	//			MPEGlayer layer;
	//			int hasNotCRC;
	//			int idBitRate;
	//			int idSampleRate;
	//			int padding;
	//			int reserve;
	//			MPEGchannelMode modeChannel;
	//			MPEGextenedMode modeExtension;
	//			int copyright;
	//			int original;
	//			int emphasis;
	//		}headerInfo;
	//		int frameLength;
	//		int bitRate;
	//		int sampleRate;
	//		int channels;
	//		//֡��
	//		struct{
	//			int mainDataOff;					//������ƫ��
	//			int privateBits;					//���õ�˽��λ
	//			struct{
	//				int scfsi;						//ѡ����Ϣ
	//				struct{
	//					int part23length;			//������λ��
	//					int bigValues;				//��ֵ
	//					int globalGain;				//ȫ������
	//					int scaleFacCompress;		//��������ѹ��
	//					int flagWindowSwitch;		//���л���־
	//					union{
	//						struct{
	//							int blockType;		//������
	//							int mixedFlag;		//�Ƿ��ǻ�Ͽ�
	//							int tableSelect[2];	//��ѡ��
	//							int subblockGain[3];//�ӿ�����
	//						}wMode1;
	//						struct{
	//							int tableSelect[3];	//��ѡ��
	//							int region0Count;	//����0-����
	//							int region1Count;	//����1-����
	//						}wMode0;
	//					};
	//					int preflag;				//Ԥ��־
	//					int scaleFacScale;			//������������
	//					int count1TableSelect;		//����1��ѡ��
	//				}gr[2];
	//			}ch[2];
	//		}sideInfo;
	//		int mainDataBegin;
	//		int mainDataEnd;
	//		stream originData;
	//	};
	//	class MPEGobject{
	//	public:
	//		TagID3V2 info1;
	//		TagID3V1 info2;
	//		std::vector<MPEGframe> frames;
	//		stream audioData;
	//	public:
	//		bool seekSync(stream &s);
	//		bool load(const stream &s);
	//	};
	//}
}