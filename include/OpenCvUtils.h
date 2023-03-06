//
// Created by zhichao.tian on 2021/4/19.
//

#ifndef VIDEO_OPENCVUTILS_H
#define VIDEO_OPENCVUTILS_H

#include <iostream>


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class OpenCvUtils {

private:

public:

    void OpenCvUsb(int videoIndex, int w, int h, int fps);
    void OpenCvRtsp(const std::string& rtsp, int w, int h, int fps);

    void Show(int w, int h);

};


#endif //VIDEO_OPENCVUTILS_H
