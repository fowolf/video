//
// Created by zhichao.tian on 2021/4/22.
//

#ifndef VIDEO_DEFINE_H
#define VIDEO_DEFINE_H

#include <cstring>
#include <vector>
#include <unistd.h>
#include <iostream>

using namespace std;
#define IRDCAMURL "http://localhost:8082/irdcam"

enum CameraLink
{
    USB = 1,
    IP = 2,
    JPG_FILE = 100,
};

typedef struct
{
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

#define LOG4CPP_FORMAT "[%d-%c]-[%p] - %m%n"

struct M3u8TS
{
    string ts_url;
    double duration;

    bool operator<(M3u8TS b) const
    {
        return ts_url < b.ts_url;
    }
};


#define LOG4CPP_FILE_SIZE 20 * 1024 * 1024
#define LOG4CPP_FILE_BACKUP 10
#endif // VIDEO_DEFINE_H
