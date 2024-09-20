#include "hashmap.hpp"

bool Hashmap::need_resize()
{
  return load_factor * mem.size() < elements;
}

void Hashmap::update_mem()
{
  //if there is no need to resize then we do nothing
  if(!need_resize()) return;
  //TODO: implement resize logic
  auto contents = get_all();
  //reset mem, increasing the size twofold
  mem = (typeof(mem))(2*mem.size());
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
  unsigned int hash = hash_function(key, mem.size());
  for(auto&[c_key, val] : mem[hash])
  {
    if(c_key == key) return val;
  }
  //add a dummy element in case there is no element with that key
  mem[hash].push_back({key, 0});
  //increment the elements since this is a new element we are adding
  elements++;
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

