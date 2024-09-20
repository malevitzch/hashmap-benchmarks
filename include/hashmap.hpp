#include <string>
#include <vector>
#include <functional>


//this is not a generic implementation since we need it for only one usecase, basicaly supposed to be std::unordered_map<std::string, int>
class Hashmap
{
private:
  //we store all of our stuff here
  std::vector<std::vector<std::pair<std::string, int>>> mem;
  std::function<unsigned int(std::string, unsigned int mod)> hash_function;
  unsigned int elements = 0;
  //the ratio of elements to memory
  float load_factor;
  //a function that returns whether or not there are enough elements in the hashmap to warrant a resize
  bool need_resize();
  //a function that resizes the hashmap if needed
  void update_mem();
  
public:
  Hashmap() = delete;
  Hashmap(unsigned int mem_size, float load_factor, typeof(hash_function) hash_function);
  //access operator
  int& operator[](std::string key);
  //checks if key is present in map
  bool contains(std::string key);
  //flattens the hashmap to a vector of <key, value> pairs (since I assume we don't want to implement iterators cause I for sure don't)
  std::vector<std::pair<std::string, int> > get_all();
};
