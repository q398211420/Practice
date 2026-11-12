file(GLOB_RECURSE algo_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(DataStructureTest ${algo_src})
target_link_libraries(DataStructureTest PRIVATE gtest gtest_main pthread)
gtest_discover_tests(DataStructureTest)

