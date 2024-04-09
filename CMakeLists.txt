cmake_minimum_required (VERSION 3.14)
PROJECT(ZjuMatrix)

# 查找ZjuMatrix目录下的所有*.cpp源文件和*.h头文件,并将文件列表保存到 SOURCE_DIR_LIST和HEADER_DIR_LIST 变量
# Find all *.cpp source files and *.h head files in ZjuMatrix/, and then save the file lists to the variable  SOURCE_DIR_LIST and HEADER_DIR_LIST
FILE(GLOB SOURCE_DIR_LIST "ZjuMatrix/*.cpp")	
FILE(GLOB HEADER_DIR_LIST "ZjuMatrix/*.h")            

# 将SOURCE_DIR_LIST和HEADER_DIR_LIST中文件列表以静态库的方式加入工程
# add the file lists of SOURCE_DIR_LIST and HEADER_DIR_LIST into the project ZjuMatrix in the form of static library
ADD_LIBRARY(ZjuMatrix STATIC ${SOURCE_DIR_LIST} ${HEADER_DIR_LIST})
 
# 打印SOURCE_DIR_LIST和HEADER_DIR_LIST列表信息
# MESSAGE(STATUS "SOURCE_DIR_LIST = ${SOURCE_DIR_LIST}")		
# MESSAGE(STATUS "HEADER_DIR_LIST = ${HEADER_DIR_LIST}")		

# 配置data文件
# configure data files
CONFIGURE_FILE(examples/exampleOne/examOne_f.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
CONFIGURE_FILE(examples/exampleOne/examOne_gK.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
CONFIGURE_FILE(examples/exampleTwo/ExamTwo_gM.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
CONFIGURE_FILE(examples/exampleTwo/ExamTwo_gK.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

# 遍历获取examples/exampleOne/路径下所有的*.cpp文件列表
# Traverse to obtain a list of all *. cpp files in the path of examples/exampleOne/
FILE(GLOB EXAMPLEONESOURCE_DIR_LIST "examples/exampleOne/*.cpp")	
# 将EXAMPLEONESOURCE_DIR_LIST中文件列表生成可执行文件
# Generate an executable file from the file list EXAMPLEONESOURCE_DIR_LIST
ADD_EXECUTABLE(ZjuMatrixExampleOne ${EXAMPLEONESOURCE_DIR_LIST})

#遍历获取examples/exampleTwo/路径下所有的*.cpp文件列表
# Traverse to obtain a list of all *. cpp files in the path of examples/exampleTwo/
FILE(GLOB EXAMPLETWOSOURCE_DIR_LIST "examples/exampleTwo/*.cpp")	
# 将EXAMPLETWOSOURCE_DIR_LIST中文件列表生成可执行文件
# Generate an executable file from the file list EXAMPLETWOSOURCE_DIR_LIST
ADD_EXECUTABLE(ZjuMatrixExampleTwo ${EXAMPLETWOSOURCE_DIR_LIST})

#遍历获取tests/路径下所有的*.cpp文件列表
# Traverse to obtain a list of all *. cpp files in the path of tests/
FILE(GLOB TESTSOURCE_DIR_LIST "tests/*.cpp")	
# 将TESTSOURCE_DIR_LIST中文件列表生成可执行文件
# Generate an executable file from the file list TESTSOURCE_DIR_LIST
ADD_EXECUTABLE(ZjuMatrixTest ${TESTSOURCE_DIR_LIST})

#在ZjuMatrixExampleOne中添加ZjuMatrix库
# include ZjuMatrix library in ZjuMatrixExampleOne
TARGET_LINK_LIBRARIES(ZjuMatrixExampleOne PRIVATE ZjuMatrix)
#在ZjuMatrixExampleTwo中添加ZjuMatrix库
# include ZjuMatrix library in ZjuMatrixExampleTwo
TARGET_LINK_LIBRARIES(ZjuMatrixExampleTwo PRIVATE ZjuMatrix)
#在ZjuMatrixTest中添加ZjuMatrix库
# include ZjuMatrix library in ZjuMatrixTest
TARGET_LINK_LIBRARIES(ZjuMatrixTest PRIVATE ZjuMatrix)