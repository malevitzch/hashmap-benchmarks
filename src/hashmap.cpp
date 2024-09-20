#include "hashmap.hpp"

//NOTE: recommended initial_mem_size is 16, definitely more for the project, load_factor probably around 0.9-1 maybe higher but this needs tests (performance degrades quite fast with higher load factors)
Hashmap::Hashmap(unsigned int initial_mem_size, float load_factor, typeof(hash_function) hash_function) : mem(initial_mem_size), hash_function(hash_function), load_factor(load_factor)
{

}

int& Hashmap::operator[](std::string key)
{
  
}

bool Hashmap::contains(std::string key)
{
  
}

std::vector<std::pair<std::string, int> > Hashmap::get_all()
{

}

