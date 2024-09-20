#include <iostream>
#include <functional>
#include "hashfunc.hpp"
#include "hashmap.hpp"

int main()
{
  auto example_poly = std::bind(polynomial_hash, 743, std::placeholders::_2, std::placeholders::_1);
  Hashmap map(16, 0.9, example_poly);
  for(int i = 0; i < 100; i++)
  {
      map[std::to_string(i)] = i;
  }
  for(int i = 0; i < 100; i++) std::cout<<i<<": "<<map[std::to_string(i)]<<"\n";
}
