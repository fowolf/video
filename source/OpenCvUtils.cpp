
#include "../include/OpenCvUtils.h"



void OpenCvUtils::OpenCvUsb(int videoIndex, int w, int h, int fps) {
    cv::VideoCapture camera;
    camera.open(videoIndex);
    camera.set(cv::CAP_PROP_FOURCC, 'GPJM');
    camera.set(cv::CAP_PROP_FRAME_WIDTH, w);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, h);
    camera.set(cv::CAP_PROP_FPS, fps);
    while (true) {
        cv::Mat image;
        camera >> image;
        std::cout << camera.get(cv::CAP_PROP_FPS) << " fps:" << fps << std::endl;
        cv::imwrite("/dev/shm/ddd.bmp", image);
//        cv::resize(image, image, cv::Size(1280, 720));
        rename("/dev/shm/ddd.bmp", "/dev/shm/bbb.bmp");
//
        cv::imshow("Display Image", image);
        int key = cv::waitKey(1);
        if ((char) key == 'q') {
            break;
        }
    }
}


void OpenCvUtils::Show(int w, int h) {

}

void OpenCvUtils::OpenCvRtsp(const std::string& rtsp, int w, int h, int fps) {
    cv::VideoCapture camera;
    camera.open(rtsp);
    camera.set(cv::CAP_PROP_FOURCC, 'GPJM');
    camera.set(cv::CAP_PROP_FRAME_WIDTH, w);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, h);
    camera.set(cv::CAP_PROP_BUFFERSIZE, 0);
    camera.set(cv::CAP_PROP_TRIGGER_DELAY, 100);
    camera.set(cv::CAP_PROP_FPS, fps);
    while (true) {
        cv::Mat image;
        camera >> image;
        std::cout << camera.get(cv::CAP_PROP_FPS) << " fps:" << fps << std::endl;
        cv::imwrite("/dev/shm/ddd.bmp", image);
//        cv::resize(image, image, cv::Size(1280, 720));
        rename("/dev/shm/ddd.bmp", "/dev/shm/bbb.bmp");
//
        cv::imshow("Display Image", image);
        int key = cv::waitKey(1);
        if ((char) key == 'q') {
            break;
        }
    }
}
