cmake_minimum_required(VERSION 3.26)
set(CMAKE_BUILD_TYPE Debug)
project(demo)
set(CMAKE_CXX_FLAGS  "-std=c++11")   
# 将当前目录下所有源文件放到变量SRC中
aux_source_directory(./src/ src)

# 遍历所有源文件
foreach(src ${src})
    # 获取文件名
    get_filename_component(target ${src} NAME_WE)
    # 生成可执行文件
    add_executable(${target} ${src})
endforeach()