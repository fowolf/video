//
// Created by zhichao.tian on 2021/4/22.
//

#ifndef VIDEO_DEFINE_H
#define VIDEO_DEFINE_H

#include <cstring>
#include <vector>

using namespace std;
#define IRDCAMURL "http://localhost:8082/irdcam"

enum CameraLink {
    USB = 1,
    IP = 2,
    JPG_FILE = 100,
};

typedef struct {
    int type;
    int link;
    std::string model;
    std::string mac;
    std::string sn;
    std::string ip;
    std::string url;
    std::string tempIp;
    int tempPort;
    vector<int> video;
    std::string rtsp;
} CameraConf;



#endif //VIDEO_DEFINE_H
