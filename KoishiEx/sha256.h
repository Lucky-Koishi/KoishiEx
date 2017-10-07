#pragma once

#include <string>

typedef unsigned __int8  uint8_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

class SHA256 //: public Hash
{
public:
  /// split into 64 byte blocks (=> 512 bits), hash is 32 bytes long
  enum { BlockSize = 512 / 8, HashBytes = 32 };

  /// same as reset()
  SHA256();

  /// compute SHA256 of a memory block
  std::string operator()(const void* data, size_t numBytes);
  /// compute SHA256 of a string, excluding final zero
  std::string operator()(const std::string& text);

  /// add arbitrary number of bytes
  void add(const void* data, size_t numBytes);

  /// return latest hash as 64 hex characters
  std::string getHash();
  /// return latest hash as bytes
  void        getHash(unsigned char buffer[HashBytes]);

  /// restart
  void reset();

private:
  /// process 64 bytes
  void processBlock(const void* data);
  /// process everything left in the internal buffer
  void processBuffer();

  /// size of processed data in bytes
  uint64_t m_numBytes;
  /// valid bytes in m_buffer
  size_t   m_bufferSize;
  /// bytes not processed yet
  uint8_t  m_buffer[BlockSize];

  enum { HashValues = HashBytes / 4 };

  /// hash, stored as integers
  uint32_t m_hash[HashValues];
};
