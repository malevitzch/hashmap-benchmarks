add_executable(benchmark benchmark.cpp hashfunc.cpp)
target_include_directories(benchmark PRIVATE ${CMAKE_SOURCE_DIR}/include)
