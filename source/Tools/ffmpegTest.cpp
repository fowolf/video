#include <iostream>
#include "ApiUtils.h"
#include "FFmpegUtil.h"
#include "OpenCvUtils.h"
#include "CTimeUtils.h"
// #include "CSystemUtils.h"

#include "CLogUtils.h"
#include "CFileUtils.h"
#include "CStringUtils.h"
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

    FFmpegUtil::openTs("/home/pi/cue_gitlab/video/1642212017465.ts");
    return 0;
}

int testStringUtils(int argc, char **argv)
{
    string a = " a \r\n";
    printf("a=[%s]\n", a.c_str());
    printf("a.strip()=[%s]\n", CStringUtils::Strip(a).c_str());
    printf("a.lstrip()=[%s]\n", CStringUtils::Lstrip(a).c_str());
    printf("a.rstrip()=[%s]\n", CStringUtils::Rstrip(a).c_str());
    printf("============================\n");

    string empty = "\r\n          \n";
    printf("empty=[%s]\n", empty.c_str());
    printf("empty.strip()=[%s]\n", CStringUtils::Strip(empty).c_str());
    printf("empty.lstrip()=[%s]\n", CStringUtils::Lstrip(empty).c_str());
    printf("empty.rstrip()=[%s]\n", CStringUtils::Rstrip(empty).c_str());
    printf("========================\n");

    empty = "aa, bb, cc , dc , xx, ";
    printf("empty=[%s]\n", empty.c_str());
    auto array = CStringUtils::Split(empty, ",");
    printf("%ld\n", array.size());
    for (auto x : array)
    {
        x = CStringUtils::Strip(x);
        if ("" == x)
            continue;
        if (CStringUtils::StartsWith(x, "a"))
            printf("start a %s\n", x.c_str());
        if (CStringUtils::EndsWith(x, "b"))
            printf("end b %s\n", x.c_str());
        printf("%s\n", CStringUtils::Strip(x).c_str());
    }
    printf("========================\n");
    return 0;
}