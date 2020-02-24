#pragma once
#include "koishiex.h"

using namespace Koishi;
namespace KoishiSHA256{
	inline dword rotate(dword a, dword c);
	inline dword swap(dword x);
	inline dword f1(dword e, dword f, dword g);
	inline dword f2(dword a, dword b, dword c);
	class SHA256{
	public:
		enum { BlockSize = 512 / 8, HashBytes = 32 };
		SHA256();
		str operator()(const void* data, size_t numBytes);
		str operator()(const str& text);
		void add(const void* data, size_t numBytes);
		str getHash();
		void getHash(unsigned char buffer[HashBytes]);
		void reset();

	private:
		enum { HashValues = HashBytes / 4 };
		void processBlock(const void* data);
		void processBuffer();
		ulongex m_numBytes;
		size_t m_bufferSize;
		uchar m_buffer[BlockSize];
		dword m_hash[HashValues];
	};
}
