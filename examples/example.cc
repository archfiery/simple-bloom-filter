#include "../bloom_filter.h"
#include <cassert>
#include <iostream>

using namespace std;

double truePercent(const vector<bool>& vec)
{
  auto size = vec.size();
  if (size == 0) return 0;
  auto counter = 0;
  for (auto e : vec) {
    if (!e) counter++;
  }
  return counter / (double) size;
}

int main()
{
  BloomFilter<uint32_t, uint64_t> bf(200, 8);
  for (auto i = 0; i < 500; i++)
    bf.add(i * 2);

  for (auto i = 0; i < 500; i++)
    assert(bf.contains(i * 2));

  vector<bool> vec;
  for (auto i = 0; i < 500; i++) {
    auto x = 2 * i + 1;
    vec.push_back(bf.contains(x));
  }

  cout << "The percentage of true from 1 to 1000 is "
       << truePercent(vec)
       << endl;

  return 0;
}
