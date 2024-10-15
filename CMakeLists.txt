cmake_minimum_required(VERSION 3.26)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
project(demo)
#enable_testing()
set(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include/gtest)
set(MY_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)
set(GTEST_LIB_DIRS ${CMAKE_SOURCE_DIR}/lib)
include(GoogleTest)
include_directories(${GTEST_INCLUDE_DIRS} ${MY_INCLUDE_DIRS})
link_directories(${GTEST_LIB_DIRS})

# 将当前目录下所有源文件放到变量SRC中
aux_source_directory(./src/ src)
#add_compile_options()
# 遍历所有源文件
foreach(src ${src})
    # 获取文件名
    get_filename_component(target ${src} NAME_WE)
    # 生成可执行文件
    add_executable(${target} ${src})
    target_link_libraries(${target} PRIVATE gtest gtest_main pthread)
    #gtest_discover_tests(${target})
endforeach()
add_subdirectory(multifiletest)
add_subdirectory(src/DynamicLinking src/DynamicLinking)
