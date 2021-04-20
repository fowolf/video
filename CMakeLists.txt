#cmake_minimum_required(VERSION 3.17)
project(video)

set(CMAKE_CXX_STANDARD 14)
find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)
pkg_check_modules(avcodec libavcodec REQUIRED)
pkg_check_modules(swscale libswscale REQUIRED)
pkg_check_modules(avutil libavutil REQUIRED)

add_library(${PROJECT_NAME}_lib source/FFmpegUtil.cpp include/FFmpegUtil.h source/OpenCvUtils.cpp include/OpenCvUtils.h)
target_link_libraries(${PROJECT_NAME}_lib
        ${OpenCV_LIBS}
        ${avcodec_LIBRARIES}
        ${swscale_LIBRARIES}
        ${avutil_LIBRARIES}
        )

add_executable(video main.cpp )
target_link_libraries(video
        ${PROJECT_NAME}_lib
        )