#include <iostream>
#include <functional>
#include "hashfunc.hpp"

int main()
{
  auto example_poly = std::bind(polynomial_hash, 743, 104729, std::placeholders::_1);
  std::string hello = "Hello Hashmap";
  std::cout<<example_poly(hello);
}
