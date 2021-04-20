#include <iostream>
#include "include/OpenCvUtils.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    OpenCvUtils openCvUtils = OpenCvUtils();
//    openCvUtils.OpencvUsb(0, 1920, 1080, 20);
    openCvUtils.OpencvRtsp("rtsp://admin:xyab1234@172.29.144.48/h264/ch2/main/av_stream", 1920, 1080, 20);

    return 0;
}
