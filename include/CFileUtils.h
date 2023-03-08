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

using namespace std;

class CFileUtils
{
public:
    static bool isFileExists(const char *fname)
    {
        fstream fs;
        fs.open(fname, ios::in);

        if (!fs)
        {
            return false;
        }
        return true;
    }

    static bool fileCreate(const char *fname)
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

    static bool checkAndCreate(const char *dirName)
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
};

#endif // VIDEO_CFILEUTILS_H
