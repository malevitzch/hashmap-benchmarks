#include <iostream>
#include <functional>
#include "hashfunc.hpp"
#include "hashmap.hpp"

int main()
{
  auto example_poly = std::bind(polynomial_hash, 743, std::placeholders::_2, std::placeholders::_1);
  Hashmap map(16, 0.9, example_poly);
  for(int i = 0; i < 1000000; i++)
  {
      map[std::to_string(i)] = i;
  }
  std::cout<<"["<<map.opcalls<<"]\n";
  for(int i = 0; i < 1000000; i++) 
  {
    if(i != map[std::to_string(i)]) std::cout<<"ERROR\n";
  }
}
