#include <iostream>
#include <functional>
#include "hashfunc.hpp"
#include "hashmap.hpp"
#include <unordered_map>

int main()
{
  auto example_poly = std::bind(polynomial_hash, 743, std::placeholders::_2, std::placeholders::_1);
  Hashmap map(16, 0.7, fnv1a_hash);
  //std::unordered_map<std::string, int> map;
  for(int i = 0; i < 10000000; i++)
  {
      map[std::to_string(i)] = i;
  }
  //std::cout<<"["<<map.opcalls<<"]\n";
  for(int i = 0; i < 10000000; i++) 
  {
    if(i != map[std::to_string(i)]) std::cout<<"ERROR\n";
  }
}
