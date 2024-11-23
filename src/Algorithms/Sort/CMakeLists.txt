# 在子级 CMakeLists.txt 中收集子级源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_SUB)

# 将子级的源文件合并后传递给父级
set(algo_src ${algo_src} ${SRC_SUB} PARENT_SCOPE)
#message(STATUS "SRC_SUB from child: ${src}")



