#include "hashfunc.hpp"
#include <cstdint>

unsigned int polynomial_hash(unsigned int base, unsigned int modulo, std::string input)
{
  unsigned int hash = 0;
  for(char ch : input)
  {
    hash += ch;
    hash *= base;
    hash %= modulo;
    //there might be overflows but for unsigned integers in c++ this is intended behavior
    //although when translating that might be a problem sometimes
  }
  return hash;
}

unsigned int fnv1a_hash(std::string input, unsigned int modulo)
{
  const unsigned int FNV_prime = 0x01000193;
  unsigned int hash = 0x811C9DC5;
  for(char ch : input)
  {
    hash ^= static_cast<uint8_t>(ch);
    hash *= FNV_prime;
  }
  return hash % modulo;
}
