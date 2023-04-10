#include <iostream>

// #include "CSystemUtils.h"

#include "CLogUtils.h"
#include "CFileUtils.h"
#include "CM3u8Utils.h"
#include "CFps.h"

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
    string m3u8Path = "/home/pi/cue_gitlab/video/index.m3u8";

    auto curTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    vector<M3u8TS> lines;
    auto ret = CM3u8Utils::ReadFile(m3u8Path.c_str(), lines);

    for (auto i = 0; i < lines.size(); i++)
    {
        auto line = lines[i];
        auto testPath = CFileUtils::PathJoin({"/opt/video/record/hls/C0001", "../", "test", "xxxx", line.ts_url});
        // printf("%s", testPath.c_str());
        line.ts_url = CFileUtils::AbsPath(testPath);
        // printf("%f: %s\n", line.duration, line.ts_url.c_str());
    }
    auto lastTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    printf("%ld - %ld = %ld", lastTime, curTime, lastTime - curTime);
    return 0;
}
