#include "hashfunc.hpp"

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

