#include "hashmap.hpp"
#include <iostream>
#include <cstdint>
unsigned int Hashmap::fnv1a_hash(std::string input)
{
  const unsigned int FNV_prime = 0x01000193;
  unsigned int hash = 0x811C9DC5;
  for(char ch : input)
  {
    hash ^= static_cast<uint8_t>(ch);
    hash *= FNV_prime;
  }
  return hash & (mem.size() - 1);
}
bool Hashmap::need_resize()
{
  return load_factor * mem.size() < elements;
}

void Hashmap::update_mem()
{
  auto contents = get_all();

  //this is debug, ignore
  //std::cout<<"Elements: " << elements << " Resized from " << mem.size() << " to " << mem.size()*2 << "\n";
  
  //reset mem, increasing the size twofold
  mem = std::vector<std::vector<std::pair<std::string, int>>>(mem.size() * 2);
  elements = contents.size();
  for(auto&[key, val] : contents)
  {
    unsigned int hash = fnv1a_hash(key);
    mem[hash].push_back({key, val});
  }
}
//NOTE: recommended initial_mem_size is 16, definitely more for the project, load_factor probably around 0.9-1 maybe higher but this needs tests (performance degrades quite fast with higher load factors)
Hashmap::Hashmap(unsigned int initial_mem_size, float load_factor)
  : mem(initial_mem_size), load_factor(load_factor) {}

int& Hashmap::operator[](std::string key)
{
  unsigned int hash = fnv1a_hash(key);
  for(auto&[c_key, val] : mem[hash])
  {
    if(c_key == key) return val;
  }
  //add a dummy element in case there is no element with that key
  //increment the elements since this is a new element we are adding
  elements++;
  //in case we have too many elements, we need to reorganize the whole hashmap
  if(need_resize())
  {
    update_mem();
    //we call the function recursively to get the reference to the object on the new updated map
    return (*this)[key];
  }
  mem[hash].push_back({key, 0});
  //return a reference to the new element so that you can do: map[x] = 10;
  return mem[hash].back().second;
}

bool Hashmap::contains(std::string key)
{
  unsigned int hash = fnv1a_hash(key);
  for(auto& el : mem[hash]) if(el.first == key) return true;
  return false;
}

std::vector<std::pair<std::string, int> > Hashmap::get_all()
{
  std::vector<std::pair<std::string, int> > res;
  for(auto& vec : mem)
  {
    for(auto& el : vec) res.push_back(el);
  }
  return res;
}

