aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} algo_src)

add_subdirectory(Sort)
add_executable(MyAlgorithmsTest ${algo_src})
target_link_libraries(MyAlgorithmsTest PRIVATE gtest gtest_main pthread)
gtest_discover_tests(MyAlgorithmsTest)

