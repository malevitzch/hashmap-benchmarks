#include <iostream>
#include <functional>
#include "hashfunc.hpp"
#include "hashmap.hpp"

int main()
{
  auto example_poly = std::bind(polynomial_hash, 743, std::placeholders::_2, std::placeholders::_1);
  Hashmap map(16, 0.9, example_poly);
  map["test"] = 3;
  std::cout<<map["test"];
}
