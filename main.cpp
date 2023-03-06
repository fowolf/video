#include <iostream>
// #include "boost/"
// #include <chrono>
#include "include/ApiUtils.h"
#include "include/FFmpegUtil.h"
#include "include/OpenCvUtils.h"
#include "include/CTimeUtils.h"

#include "include/CLogUtils.h"

using namespace std;

int testLog();
int main()
{
    testLog();
    // auto now = std::chrono::system_clock::now();
    // cout << "now is: " << now << endl;
    // string t_s =  CTimeUtils::ToString(now, std::string("%04Y-%02m-%02d %H:%M:%S"));
    // cout << "tostring:" << t_s << endl;

    // time_t tt = CTimeUtils::ToTime(t_s, std::string("%04Y-%02m-%02d %H:%M:%S"));
    // cout << "ToTime:" << tt << endl;
}

int testLog()
{
    time_t now = time(nullptr);
    // CLogUtils &logger = CLogUtils::getInstance();
    auto &logger = CLogUtils::getCatInstance("main");
    logger.error("..............");
    logger.info("..............");

    auto &logger1 = CLogUtils::getCatInstance("main1");
    logger1.error("..............");
    logger1.info("..............");

    auto &logger2 = CLogUtils::getCatInstance("main2");
    logger2.error("..............");
    logger2.info("..............");

    auto &logger3 = CLogUtils::getCatInstance("main");
    logger3.error("..............%d", 11123);
    logger3.info("..............");

    ostringstream logInfo;
    logInfo << "now tmsp is:" << now;
    string _logInfo = logInfo.str();
    logger.info(_logInfo.c_str());
    logger.info("now tmsp is: [%ld]", now);

    string t_s = CTimeUtils::ToString(now, std::string("%04Y-%02m-%02d %H:%M:%S"));

    logger.info("tostring: %s, %ld", t_s.c_str(), now);

    time_t tt = CTimeUtils::ToTime(t_s, std::string("%04Y-%02m-%02d %H:%M:%S"));
    logger.info("ToTime: %ld", tt);
}

int main1()
{
    std::cout << "Hello, World!" << std::endl;

    vector<CameraConf> camVector = ApiUtils::GetCamList();
    std::cout << camVector.size() << std::endl;
    CameraConf *visiCamera;
    for (auto &i : camVector)
    {
        std::cout << i.model << std::endl;
        if (!i.video.empty())
            std::cout << i.video[0] << std::endl;
        if (i.link == CameraLink::IP)
        {
            visiCamera = &i;
        }
    }

    OpenCvUtils openCvUtils = OpenCvUtils();
    openCvUtils.OpenCvUsb(0, 1920, 1080, 20);
    // // if (nullptr != visiCamera) {
    // //     std::cout << visiCamera->rtsp << endl;
    // //     FFmpegUtil::openRtsp(visiCamera->rtsp);
    // // }
    // long a = 280;
    // std::cout << (double)a / 1000 << std::endl;

    return 0;
}
