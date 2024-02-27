project(lexical)

set(CMAKE_CXX_STANDARD 11)

add_library(lexical tokenizer.cpp)

target_link_libraries(lexical PRIVATE config)

target_include_directories(lexical PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(regularEngine regularEngine.cpp)

target_include_directories(regularEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})