//
// Created by zhichao.tian on 2021/4/9.
//

#include "../include/FFmpegUtil.h"


FFmpegUtil::FFmpegUtil() {
    this->videoIndex = -1;
}

void FFmpegUtil::openUsb(int usbVideoIndex) {
    this->videoIndex = usbVideoIndex;


}

int FFmpegUtil::initDecodeVideo() {
    //注册库中所有可用的文件格式和解码器
    av_register_all();
    //注册所有设备,主要用于本地摄像机播放支持
    avdevice_register_all();

    AVDictionary *options = NULL;
    AVCodec *deCodec = NULL;       //解码器



    return 0;
}
