//
// Created by myuserid on 2021/4/30.
//

#ifndef VIDEO_CFILEUTILS_H
#define VIDEO_CFILEUTILS_H
#include <iostream>
#include <fstream>
// #include <sys/stat.h>
// #include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include <filesystem>

// #include "CStringUtils.h"

using namespace std;

class CFileUtils
{
public:
    static bool IsFileExists(const char *fname)
    {
        fstream fs;
        fs.open(fname, ios::in);

        if (!fs)
        {
            return false;
        }
        return true;
    }

    static bool FileCreate(const char *fname)
    {
        fstream fs;
        fs.open(fname, ios::in);

        if (!fs)
        {
            printf("%s file not exists, create it\n", fname);
            ofstream fout(fname);
            if (fout)
            {
                fout.close();
            }
        }
        return true;
    }

    static bool CheckAndCreate(const char *dirName)
    {

        // struct stat buf;
        // if (lstat(dirName, &buf) < 0)
        // {
        //     auto flag = mkdir(dirName, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
        //     if (flag == 0){
        //         return true;
        //     }
        //     return false;
        // }

        // if (S_ISREG(buf.st_mode))
        // {
        //     printf("%s is file \n", dirName);
        //     return true;
        // }
        // if (S_ISDIR(buf.st_mode))
        // {
        //     return true;
        // }
        //         printf("%s exists but not a dir, is %x \n", dirName, buf.st_mode);
        // return false;

        DIR *tmpDir = NULL;
        tmpDir = opendir(dirName); // 打开目录
        if (tmpDir == NULL)
        {
            auto flag = mkdir(dirName, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            if (flag == 0)
            {
                return true;
            }
            return false;
        }
        return true;
    }

    static bool ReadLines(const char *filePath, vector<string> &out)
    {
        if (!IsFileExists(filePath))
        {
            return false;
        }

        ifstream readFile;
        readFile.open(filePath, ios::in);

        if (readFile.is_open())
        {
            string str;
            while (getline(readFile, str))
            {
                // str = CStringUtils::Strip(str);
                out.push_back(str);
            }
            readFile.close();
        }
        return true;
    }

    static string PathJoin(initializer_list<std::string> pathList)
    {
        string ret = "";
        size_t i = 0;
        auto size = pathList.size();
        for (auto p : pathList)
        {
            if (i < size - 1)
            {
                while (p.back() == '/' || p.back() == '\\')
                {
                    p = p.substr(0, p.size() - 1);
                }
            }
            if (i > 0)
            {
                while (p.front() == '/' || p.front() == '\\')
                {
                    p = p.substr(1);
                }
            }
            ret.append(p);
            if (i < size - 1)
            {
                ret.append("/");
            }

            i++;
        }
        return ret;
    }

    static string AbsPath(string path)
    {
        // char dir[PATH_MAX] = "";
        // realpath(path.c_str(), dir);
        // printf("absPath  %s --> %s\n", path.c_str(), dir);
        // return string(dir);
        auto _abs = std::filesystem::absolute(path);
        return _ReBuildPath(_abs);
        // return _abs;
    }

private:
    static string _ReBuildPath(const std::string &s)
    {
        vector<string> result;
        int pos;
        string temp = s;
        while ((pos = temp.find_first_of("/")) != temp.npos)
        {
            if (pos > 0)
            {
                auto value = temp.substr(0, pos);
                if (".." == value)
                {
                    if (result.size() > 0)
                    {
                        result.pop_back();
                    }
                }
                else if ("." != value)
                {
                    result.push_back(value);
                }
            }
            temp = temp.substr(pos + 1);
        }
        if (temp.length() > 0)
        {
            if (".." == temp)
            {
                if (result.size() > 0)
                {
                    result.pop_back();
                }
            }
            else if ("." != temp)
            {
                result.push_back(temp);
            }
        }
        string ret = "";
        for (auto ele : result)
        {
            ret.append("/" + ele);
        }
        return ret;
    };
};

#endif // VIDEO_CFILEUTILS_H
