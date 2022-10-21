cmake_minimum_required(VERSION 3.18.1)
project("msopengles2")

set(GLM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libglm)
set(STBIMG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libstbImage)
#导入头文件
include_directories(${GLM_DIR}/include)
include_directories(${STBIMG_DIR}/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sample)

#以下导入多个源文件
file(GLOB ALL_SOURCE_FILE *.cpp *.c)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sample CPP_FILES)




add_library(
        msopengles
        SHARED
        ${ALL_SOURCE_FILE}
        ${CPP_FILES}
)


find_library(
        log-lib

        log)


target_link_libraries(
        msopengles
        android
        GLESv1_CM
        GLESv2
#        GLESv3
        ${log-lib})