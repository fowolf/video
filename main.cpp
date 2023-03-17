#include <iostream>
#include "ApiUtils.h"
#include "FFmpegUtil.h"
#include "OpenCvUtils.h"
#include "CTimeUtils.h"
#include "CSystemUtils.h"

#include "CLogUtils.h"
#include "CFileUtils.h"

using namespace std;

log4cpp::Category& getLogger(string logName)
{
    std::string logPath = CSystemUtils::getLogPath();
    std::string appName = CSystemUtils::getAppName();
    std::string _logName = appName + ".log";
    CLogUtils::setLogFile(logPath + "/" + _logName);

    auto &logger = CLogUtils::getCatInstance(logName);
    return logger;
}

int main(int argc, char **argv)
{
    auto& logger = getLogger("main");
    logger.info("main is start");
    logger.info("log with: %s", CLogUtils::getLogFile().c_str());

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
