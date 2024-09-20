#include "hashmap.hpp"
#include <iostream>
bool Hashmap::need_resize()
{
  return load_factor * mem.size() < elements;
}

void Hashmap::update_mem()
{
  auto contents = get_all();

  //this is debug, ignore
  std::cout<<"Elements: " << elements << " Resized from " << mem.size() << " to " << mem.size()*2 << "\n";
  
  //reset mem, increasing the size twofold
  mem = (typeof(mem))(2*mem.size());
  elements = 0;
  for(auto&[key, val] : contents)
  {
    //this might look sus but it's just me being lazy and calling the operator rather than doing this manually
    //obviously in the final code we want as little abstraction as possible, probably best to then not reuse functions (unless binary size is what matters more than stack usage)
    (*this)[key] = val;
  }
}
//NOTE: recommended initial_mem_size is 16, definitely more for the project, load_factor probably around 0.9-1 maybe higher but this needs tests (performance degrades quite fast with higher load factors)
Hashmap::Hashmap(unsigned int initial_mem_size, float load_factor, typeof(hash_function) hash_function)
  : mem(initial_mem_size), hash_function(hash_function), load_factor(load_factor) {}

int& Hashmap::operator[](std::string key)
{
  opcalls++;
  unsigned int hash = hash_function(key, mem.size());
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
    //NOTE: this can be simply changed to not be recursive, 
    return (*this)[key];
  }
  mem[hash].push_back({key, 0});
  //return a reference to the new element so that you can do: map[x] = 10;
  return mem[hash].back().second;
}

bool Hashmap::contains(std::string key)
{
  for(auto& vec : mem)
  {
    for(auto& el : vec) if(el.first == key) return true;
  }
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

