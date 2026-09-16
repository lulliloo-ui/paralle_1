#include <iostream>
#include <vector>
#include <future>
#include <string>
#include "clicker.hpp"

using data_t = std::vector< unsigned long long >;
using value_t = data_t::value_type;

value_t sum(data_t & values, size_t start, size_t count)
{
  value_t res = 0;
  for(size_t i = start; i < start + count; ++i) {
    res += values[i];
  }
  return res;
}

int main(int argc, char * argv[])
{
  if(argc != 2) {
    std::cout << "нет количества потоков\n";
    return 1;
  }
  size_t threads = std::stoull(argv[1]);
  if(threads == 0) {
    std::cout << "нельзя запускать без потоков\n";
    return 1;
  }
  constexpr size_t size{1'000'000'000};

  size_t perThread = size / threads;
  size_t remainder = size % threads;
  std::vector< std::future< value_t > > futures;

  double init{0}, total{0};
  Clicker cl;
  data_t values(size, 1);
  init = cl.millisec();
  for(size_t i = 0; i < threads; ++i) {
    if(i == 0) {
      size_t count = perThread + remainder;
      futures.push_back(std::async(std::launch::async, sum, std::ref(values), 0, count));
    } else {
      size_t start = perThread * i + remainder;
      futures.push_back(std::async(std::launch::async, sum, std::ref(values), start, perThread));
    }
  }
  value_t res = 0;
  for (size_t i = 0; i < threads; ++i) {
    res += futures[i].get();
  }
  total = cl.millisec();
  std::cout << total - init;
  return 0;
}
