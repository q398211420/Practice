file(GLOB_RECURSE DP_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(DesignPatternsTest ${DP_src})
target_link_libraries(DesignPatternsTest PRIVATE gtest gtest_main pthread)
gtest_discover_tests(DesignPatternsTest)

