#include "../bloom_filter.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
  BloomFilter<string, uint64_t> bf(200, 8);
  bf.add("hello");
  bf.add("world");

  cout << bf.contains("hello") << endl;
  cout << bf.contains("world") << endl;
  cout << bf.contains("helloworld") << endl;

}
