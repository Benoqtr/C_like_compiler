project(config)

set(CMAKE_CXX_STANDARD 11)

add_library(config config.cpp)

target_include_directories(config PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})