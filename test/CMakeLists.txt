# config

add_executable(test_config test_config.cpp)

target_link_libraries(test_config PRIVATE config)

configure_file(${CMAKE_SOURCE_DIR}/config/grammar.bg ${CMAKE_CURRENT_BINARY_DIR}/grammar.bg COPYONLY)

configure_file(${CMAKE_SOURCE_DIR}/config/regular.br ${CMAKE_CURRENT_BINARY_DIR}/regular.br COPYONLY)

#rawToken

add_executable(test_rawToken test_rawToken.cpp)

target_link_libraries(test_rawToken PRIVATE lexical config)

configure_file(${CMAKE_SOURCE_DIR}/test/func.b ${CMAKE_CURRENT_BINARY_DIR}/func.b COPYONLY)

# thomson

# add_executable(test_thomson test_thomson.cpp)

# target_link_libraries(test_thomson PRIVATE config)

# configure_file(example.txt ${CMAKE_CURRENT_BINARY_DIR}/example.txt COPYONLY)