# 将当前目录下所有源文件放到变量SRC中
aux_source_directory(./ tmp)
#add_compile_options()

add_executable(filetest ${tmp})