#ifndef VIDEO_CSYSTEMUTILS_H
#define VIDEO_CSYSTEMUTILS_H

#pragma once
#include <iostream>
#include <unistd.h>

using namespace std;

class CSystemUtils
{
public:
    ~CSystemUtils(){};
    CSystemUtils()
    {
    }

    static std::string dirName(std::string filePath)
    {
        auto index = filePath.find_last_of("/");
        // printf("%d\n", index);
        if (index < 0)
        {
            return NULL;
        }
        auto dirName = filePath.substr(0, index);
        return dirName;
    }

    static std::string fileName(std::string filePath)
    {
        auto index = filePath.find_last_of("/");
        // printf("%d\n", index);
        if (index < 0)
        {
            return NULL;
        }
        auto _name = filePath.substr(index + 1, filePath.size());
        return _name;
    }

    static std::string getAppPath()
    {
        // if (_appPath.empty())
        // {
            // printf("new\n");
            char path[1024];
            memset(path, 0, sizeof(path));
            if (readlink("/proc/self/exe", path, sizeof(path) - 1) <= 0)
            {
                return 0;
            }

            auto appPath = string(path);
            auto appDir = dirName(appPath);
            auto appName = fileName(appPath);
            return appDir;
        //     if (!appDir.empty())
        //     {
        //         _appPath = appDir;
        //     }
        //     if (!appName.empty())
        //     {
        //         _appName = appName;
        //     }
        // }
        // return _appPath;
    }
    static std::string getAppName()
    {
        // if (_appName.empty())
        // {
            // getAppPath();
        // }
        // return _appName;

            char path[1024];
            memset(path, 0, sizeof(path));
            if (readlink("/proc/self/exe", path, sizeof(path) - 1) <= 0)
            {
                return 0;
            }

            auto appPath = string(path);
            // auto appDir = dirName(appPath);
            auto appName = fileName(appPath);
            return appName;
    }

    static std::string getLogPath()
    {
        auto appPath = CSystemUtils::getAppPath();
        return appPath.append("/logs");
    }

    static std::string getDefaultLogPath()
    {
        std::string logPath = CSystemUtils::getLogPath();
        std::string appName = CSystemUtils::getAppName();
        std::string logFileName = appName + ".log";
        return logPath + "/" + logFileName;
    }

private:
    // static std::string _appPath;
    // static std::string _appName;
};

// std::string CSystemUtils::_appPath = "";
// std::string CSystemUtils::_appName = "";

#endif