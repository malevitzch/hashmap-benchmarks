add_executable(benchmark benchmark.cpp hashfunc.cpp hashmap.cpp)
target_include_directories(benchmark PRIVATE ${CMAKE_SOURCE_DIR}/include)
