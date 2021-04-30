#include <iostream>
#include <ApiUtils.h>
#include <FFmpegUtil.h>
#include "include/OpenCvUtils.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    vector<CameraConf> camVector = ApiUtils::GetCamList();
    std::cout << camVector.size() << std::endl;
    CameraConf *visiCamera ;
    for (auto &i : camVector) {
        std::cout << i.model << std::endl;
//        if (!i.video.empty())
//            std::cout << i.video[0] << std::endl;
        if (i.link == CameraLink::IP) {
            visiCamera = &i;
        }
    }

//    OpenCvUtils openCvUtils = OpenCvUtils();
////    openCvUtils.OpencvUsb(0, 1920, 1080, 20);
//    openCvUtils.OpencvRtsp("rtsp://admin:xyab1234@172.29.144.48/h264/ch2/main/av_stream", 1920, 1080, 20);
//    FFmpegUtil fFmpegUtil = FFmpegUtil();
    if (nullptr != visiCamera) {
        std::cout << visiCamera->rtsp << endl;
        FFmpegUtil::openRtsp(visiCamera->rtsp);
//        FFmpegUtil::openRtsp("rtsp://192.168.99.7:554/live/0/MAIN");
    }

    return 0;
}
