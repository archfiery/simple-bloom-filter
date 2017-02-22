#ifndef BLOOM_FILTER_H_
#define BLOOM_FILTER_H_

#include <array>
#include <cstddef>
#include <vector>

#include "MurmurHash3.h"

template <typename K, typename V = std::hash<K> >
class BloomFilter
{
  std::vector<bool> m_bits;
  uint8_t m_numHashes;
  uint64_t m_filterSize;
public:
  BloomFilter(uint64_t size, uint8_t numHashes)
    : m_filterSize(size)
    , m_bits(size, false)
    , m_numHashes(numHashes)
  {

  }
  virtual ~BloomFilter()
  {

  }
  void add(const K& data)
  {
    std::array<V, 2> hashValue;
    hash(data, hashValue);
    
    for (auto i = 0; i < m_numHashes; i++) {
      auto pos = nthHash(hashValue[0], hashValue[1]);
      m_bits[pos] = true;
    }
  }
  bool contains(const K& data)
  {
    std::array<V, 2> hashValue;
    hash(data, hashValue);
    
    for (auto i = 0; i < m_numHashes; i++) {
      auto pos = nthHash(hashValue[0], hashValue[1]);
      if (m_bits[pos] == false)
        return false;
    }

    return true;
  }
private:
  void hash(const K& data, std::array<V, 2>& hashValue)
  {
    MurmurHash3_x64_128(&data, sizeof(data), 0, hashValue.data());
  }

  inline uint64_t nthHash(V hashA, V hashB)
  {
    return (hashA + m_numHashes * hashB) % m_filterSize;
  }
};

#endif
