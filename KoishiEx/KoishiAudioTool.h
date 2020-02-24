#include "stdafx.h"
#include "KoishiEx.h"
#include "windows.h"
#include <MMSystem.h>
#include <math.h>

#pragma once
using namespace Koishi;

namespace KoishiAudioTool{
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
			word audioFormat;	//1为PCM，其他则为各式各样的压缩方式
			word channels;
			long sampleRate;	//采样频率 单位：HZ
			long byteRate;		//单位 B/s
			word byteAlign;		//每个采样的字节数
			word bitPerSample;	//每个采样的位数（8或者16
			long extraInfo;		//总采样数，audioFormat不为1时有效
			stream rawData;		//原始数据
		public:
			bool load(stream &s);
			bool loadFile(const str &fileName);
			bool make(stream &s);
		};
	}
	//绘制波形图
	extern void makeWaveGraph(const audio &ad, int channels, matrix &mat, int width, int height);
	extern void makeWaveGraphDB(const audio &ad, int channels, matrix &mat, int width, int height);
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
		void initFormat(int channels, int bitPerSample, int sampleRate, int byteRate, int byteAlign, int cbSize);
		bool initFormat(const WAV::WAVobject &PCMwavObject);
		dword play(const stream &cPCMstream);
		dword play(const audio &ad);
		dword record();
		void stop();
		bool getData(stream &cPCMstream);
		longex getPos();
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

	//////////////////////////////////////////////////////////////
	//OGG编解码
	//////////////////////////////////////////////////////////////
	namespace OGG{
		bool OGGeasyDecode(const str &fileName, stream &pcmOut, volatile double &complete);
		bool OGGeasyDecodeAndPlay(const str &fileName);
		/////////////////////////////////////////////
		//辅助函数
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
		//超快速离散余弦变换·改自libvorbis
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
		//OGG页面
		/////////////////////////////////////////////
		typedef stream OGGpack;
		class OGGpage{
		public:
			OGGpage();
			uchar ver;
			uchar type;
			union{
				longex sampleTotalCount;
				uchar granule[8];			//颗粒参数
			};
			dword serial;					//
			dword sequence;					//页的次序
			dword checkCRC;					//校验码
			uchar segCount;					//分段数
			std::vector<uchar> segLength;	//每段段长
			std::vector<stream> segData;	//段数据
		};
		////////////////////////////////////////
		//编码本
		class VorbisCodeBook{
		private:
			typedef struct VorbisCodeBookEntry{
				VorbisCodeBookEntry();
				dword huffmanCode;				//哈夫曼编码
				long length;					//条目长度
				union{
					long originID;				//条目在编码本中的顺序
					dword value;
				};
				long weight;					//条目权重
				char codeStr[32];				//把条目读出来
			}Entry;								//条目
			typedef enum VorbisCodeBookMappingType:int{
				NO_LOOK_UP,						//没映射表
				LOOK_UP_1,						//隐式填充映射表
				LOOK_UP_2						//显式填充映射表（很少用到）
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
				dword code;						//当前节点的哈夫曼编码，已转换为双字
				int depth;						//节点深度，根节点为0，该值最大值为entryLen中的最大值-1
				bool isLeaf;					//是否是叶子，确定后不能再向下插入节点，leftOK和rightOK都为True
				bool leftOK;					//左节点悬空状况，如果左节点的状态已确定（或者为某一其他节点或者确定为不存在，即为叶节点)则定为True
				bool rightOK;					//右节点悬空状态
				long weight;
				HuffmanNode();
			}HuffmanNode;
		public:
			VorbisCodeBook();
			int dimension;						//编码本的维度
			int entryCount;						//条目数
			MappingType mappingType;			//映射类型，取值0-2，0的话，跳过对mapping参数的解析，mappingPara结构体为空。
			int ordered;						//这个条目的长度是排序的，采用不同的解析方式
			int sparsed;						//存在未使用的条目，未使用的条目不参与哈夫曼树的组成
			queue entryLen;						//每个条目的长度，用于确定该条目的哈夫曼编码
			MappingPara mappingPara;			//映射类型，取值0-2，0的话
			bool buildFromData(stream &data);	//从一个数据流中进行解析，数据流内按位指针会改变
		public:
			//解析后哈夫曼编码，长度为entryCount
			//以二进制表示时把先读的位放在小端，读法为从根节点开始读，例如读作10100，记为00...000101B，写作0x00000005
			//实际解码的时候，在解码前的数据中，按位读取时，也是从根节点开始解码
			std::vector<Entry> entries;							//已使用的条目（按权重排好序的）
			std::vector<sequence> quantized;					//量化后的值(NO_LOOK_UP无效)
			bool buildTree();
			bool unquantize();
			long findEntry(long huffmanCode, long huffmanLen);	//查找序号（自左到右的排序），找不到的话，返回-1。
			long decodeEntryIn(stream &sour);				//在一个数据流中按位查找序号
			long decodeValueIn(stream &sour);				//在一个数据流中按位查找编码，返回该编码在密码本的起始位置（原位置）数据流内按位指针会改变
			sequence decodeVectorIn(stream &sour, int vectorLen, bool interleaved);//在一个数据流中依次根据编码构建向量值，数据流内按位指针会改变（对NO_LOOK_UP无效）
			std::vector<sequence> decodeMultVectorIn(stream &sour, int vectorLen, long offset, int ch);
		};
		////////////////////////////////////////
		//时域变换（VorbisI中为保留用途）
		class VorbisTimeDomain{
		public:
			VorbisTimeDomain();
			short reserved;
			bool buildFromData(stream &data);					//从一个数据流中进行解析，数据流内按位指针会改变
		};
		////////////////////////////////////////
		//基底参数
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
				queue partitionClassList;	//partitions个元素
				long maxClass;				//partitionClassList中的最大值
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
		//残差参数
		class VorbisResidue{
		public:
			VorbisResidue();
			word residueType;
			dword begin;
			dword end;
			dword partitionSize;
			dword classification;
			dword classBook;
			queue cascade;			//串行数据组，读取book使用
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
			dword channels;		//此参数由外部赋值
			std::vector<PolarCoordinate> couplingList;
			uchar reserved;
			queue mux;			//subMaps大于1时有效，长度为通道数。
			std::vector<SubmapPara> submapList;
			bool buildFromData(stream &data);
		};
		////////////////////////////////////////
		//模式类型
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
		//以下为解析后的数据结构
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
			long mode;				//使用的mode
			long mapping;			//使用的map
			long blockSize;			//采用的blockSize
			bool flagLong;			//长窗口标志位（变长
			bool flagPrevWindow;	//前一个窗口标志位
			bool flagNextWindow;	//后一个窗口标志位
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
			sequence windowValueShort;		//短窗口值（仅左半部分，长度等于info.blockSize0 / 2
			sequence windowValueLong;		//长窗口值（仅左半部分，长度等于info.blockSize1 / 2
			std::vector<VorbisBlock> blocks;
			std::vector<sequence> pcm;
		public:
			OGGobject();
			bool load(stream &s);
			bool loadFile(const str &fileName);					//读取数据
			bool initDecoder();									//初始化解码器
			bool packDecode(int packID);						//包解码
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
}