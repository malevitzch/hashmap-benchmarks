#include <string>
unsigned int polynomial_hash(unsigned int base, unsigned int modulo, std::string input);
unsigned int fnv1a_hash(std::string input, unsigned int modulo);
