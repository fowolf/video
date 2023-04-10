#include <iostream>

#include "CLogUtils.h"
#include "CFileUtils.h"
#include "CM3u8Utils.h"
#include "FFmpegUtil.h"

using namespace std;

log4cpp::Category& getLogger(string logName)
{
    // std::string logPath = CSystemUtils::getLogPath();
    // std::string appName = CSystemUtils::getAppName();
    // std::string _logName = appName + ".log";
    // CLogUtils::setLogFile(logPath + "/" + _logName);

    auto &logger = CLogUtils::getDefaultLogger(logName);
    return logger;
}

int main(int argc, char **argv)
{
    auto& logger = getLogger("main");
    logger.info("main is start");
    logger.info("log with: %s", CLogUtils::getLogFile().c_str());

    string m3u8Path = "/home/pi/time_ring_videos/changying/2022-11-09/Cea4fc2c75efa9d13";
    vector<M3u8TS> lines;
    auto m3u8List = CM3u8Utils::ReadFile(m3u8Path, lines);
    for(auto m3u8Entity = lines.begin(); m3u8Entity < lines.end(); ++m3u8Entity){
        auto tsPath = m3u8Entity->ts_url;
        tsPath = CFileUtils::PathJoin({m3u8Path, tsPath});
        FFmpegUtil::openTs(tsPath);
    }

    return 0;
}
