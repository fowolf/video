cmake_minimum_required(VERSION 3.10)
project(video)

include_directories(./include)

set(CMAKE_CXX_STANDARD 14)
find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)
find_package(CURL REQUIRED)
find_package(Threads REQUIRED)
find_package(jsoncpp REQUIRED)

pkg_check_modules(avformat libavformat REQUIRED)
pkg_check_modules(avdevice libavdevice REQUIRED)
pkg_check_modules(avcodec libavcodec REQUIRED)
pkg_check_modules(swscale libswscale REQUIRED)
pkg_check_modules(avutil libavutil REQUIRED)

add_library(RestClient_lib source/RestClient/connection.cc include/restclient-cpp/connection.h
        source/RestClient/helpers.cc include/restclient-cpp/helpers.h
        source/RestClient/restclient.cc include/restclient-cpp/restclient.h)
target_link_libraries(RestClient_lib
        #        PUBLIC CURL::libcurl
        #        PUBLIC Threads::Threads
        libcurl.so
        libpthread.so
        )


add_library(${PROJECT_NAME}_lib include/define.h
        source/FFmpegUtil.cpp include/FFmpegUtil.h
        source/OpenCvUtils.cpp include/OpenCvUtils.h
        source/Utils/ApiUtils.cpp include/ApiUtils.h include/CFps.h include/CLogUtils.h include/CFileUtils.cpp include/CFileUtils.h)
target_link_libraries(${PROJECT_NAME}_lib
        ${OpenCV_LIBS}
        ${avformat_LIBRARIES}
        ${avdevice_LIBRARIES}
        ${avcodec_LIBRARIES}
        ${swscale_LIBRARIES}
        ${avutil_LIBRARIES}
        RestClient_lib
        jsoncpp
        )

add_executable(video main.cpp)
target_link_libraries(video
        ${PROJECT_NAME}_lib
        )