#include <iostream>
#include "ApiUtils.h"
#include "../../include/FFmpegUtil.h"
#include "OpenCvUtils.h"
#include "CTimeUtils.h"
// #include "CSystemUtils.h"

#include "CLogUtils.h"
#include "CFileUtils.h"
// #include "FFmepgUtil.h"

using namespace std;

// log4cpp::Category& getLogger(string logName)
// {
//     std::string logPath = CSystemUtils::getLogPath();
//     std::string appName = CSystemUtils::getAppName();
//     std::string _logName = appName + ".log";
//     CLogUtils::setLogFile(logPath + "/" + _logName);

//     auto &logger = CLogUtils::getCatInstance(logName);
//     return logger;
// }

int main(int argc, char **argv)
{
    auto &logger = CLogUtils::getDefaultLogger("main");
    logger.info("main is start");
    logger.info("log with: %s", CLogUtils::getLogFile().c_str());

    FFmpegUtil::openTs("/home/myuserid/c++projects/video/1642212017465.ts");
    return 0;
}
