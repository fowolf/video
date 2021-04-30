//
// Created by myuserid on 2021/4/22.
//

#ifndef VIDEO_APIUTILS_H
#define VIDEO_APIUTILS_H

#include <vector>

#include "../include/define.h"

using namespace std;

class ApiUtils {
public:
    static vector <CameraConf> GetCamList();
};


#endif //VIDEO_APIUTILS_H
