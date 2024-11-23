cmake_minimum_required(VERSION 3.26)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
project(demo)
set(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include/gtest)
set(MY_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)
set(GTEST_LIB_DIRS ${CMAKE_SOURCE_DIR}/lib)
include(GoogleTest)
include_directories(${GTEST_INCLUDE_DIRS} ${MY_INCLUDE_DIRS})
link_directories(${GTEST_LIB_DIRS})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
enable_testing()

# 将当前目录下所有源文件放到变量src，此后子级不断更新src
aux_source_directory(./src/ src)
# 添加子级
add_subdirectory(src/Algorithms)
add_subdirectory(src/CppSyntax)
add_subdirectory(src/DesignPatterns)
add_subdirectory(src/Interview)
add_subdirectory(src/MT)
add_subdirectory(src/Network)
#message(STATUS "src: ${src}")

#add_compile_options()
# 遍历所有源文件
foreach(src ${src})
    # 获取文件名
    get_filename_component(target ${src} NAME_WE)
    # 生成可执行文件
    add_executable(${target} ${src})
    #gtest_discover_tests(${target})
endforeach()
add_subdirectory(multifiletest)
add_subdirectory(src/DynamicLinking src/DynamicLinking)
