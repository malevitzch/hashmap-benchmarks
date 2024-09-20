#include <iostream>
#include "hashfunc.hpp"
#include "hashmap.hpp"


int main()
{
  Hashmap map(16, 1);
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
