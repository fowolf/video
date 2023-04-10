#ifndef CM3U8UTILS_H
#define CM3U8UTILS_H

#pragma once
#include <iostream>
#include <unistd.h>
#include <cstring>

#include "define.h"
#include "CStringUtils.h"
#include "CFileUtils.h"

using namespace std;

class CM3u8Utils
{
public:
    CM3u8Utils(){};
    ~CM3u8Utils(){};

    static bool ReadFile(std::string m3u8Path, std::vector<M3u8TS> &ts_objects)
    {
        vector<string> lines;
        auto ret = CFileUtils::ReadLines(m3u8Path.c_str(), lines);
        if (ret)
        {
            string value;
            int target_duration = 0;
            M3u8TS ts_object;
            for (auto line : lines)
            {
                line = CStringUtils::Strip(line);
                if ("" == line)
                {
                    continue;
                }
                try
                {
                    // printf("%s\n", line.c_str());
                    // if (CStringUtils::StartsWith(line, "#EXT-X-TARGETDURATION:"))
                    // {
                    //     value = CStringUtils::Strip(line.substr(22));
                    //     target_duration = atof(value.c_str());
                    //     ts_object.duration = target_duration;
                    //     continue;
                    // }
                    if (CStringUtils::StartsWith(line, "#EXTINF:"))
                    {
                        value = CStringUtils::Strip(line.substr(8));
                        ts_object.duration = atof(value.c_str());
                        continue;
                    }

                    if (!CStringUtils::StartsWith(line, "#"))
                    {
                        ts_object.ts_url = line;
                        ts_objects.push_back(ts_object);
                        continue;
                    }
                }
                catch(exception &e)
                {
                    continue;
                }
            }
            return true;
        }
        return false;
    };

private:
};

#endif