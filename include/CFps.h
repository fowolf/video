//
// Created by myuserid on 2021/4/26.
//

#ifndef VIDEO_CFPS_H
#define VIDEO_CFPS_H


#include <chrono>

using namespace std::chrono;

class CFps {

public :
    static void doFps(int fps) {

    }

    static double statFps() {
        static double fps = 0.0;
        static int frameCount = 0;
        static auto lastTime = system_clock::now();
        static auto curTime = system_clock::now();

        curTime = system_clock::now();

        auto duration = duration_cast<microseconds>(curTime - lastTime);
        double duration_s = double(duration.count()) * microseconds::period::num / microseconds::period::den;

        if (duration_s > 0)//2秒之后开始统计FPS
        {
            fps = frameCount / duration_s;
            frameCount = 0;
            lastTime = curTime;
        }

        ++frameCount;

        return fps;
    }
};


#endif //VIDEO_CFPS_H
