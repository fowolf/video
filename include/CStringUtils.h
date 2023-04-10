#ifndef CSTRINGUTILS_H
#define CSTRINGUTILS_H

#pragma once
#include <cstring>
#include <vector>
#include <unistd.h>
#include <iostream>

using namespace std;

class CStringUtils
{
public:
    CStringUtils(){};
    ~CStringUtils(){};

    static bool StartsWith(std::string src, std::string sub)
    {
        return src.find(sub) == 0;
    };

    static bool EndsWith(std::string src, std::string sub)
    {
        return src.rfind(sub) == (src.length() - sub.length());
    };

    static std::string Lstrip(const std::string &src)
    {
        if (src.front() != ' ' && src.front() != '\r' && src.front() != '\n' && src.front() != '\t')
            return src;
        for (auto index = 0u; index < src.size(); index++)
        {
            if (src[index] != ' ' && src[index] != '\r' && src[index] != '\n' && src[index] != '\t')
            {
                return src.substr(index);
            }
        }
        return "";
    };

    static std::string Rstrip(const std::string &src)
    {
        if (src.back() != ' ' && src.back() != '\r' && src.back() != '\n' && src.back() != '\t')
            return src;
        for (auto index = src.size() - 1; index >= 0; index--)
        {
            if (src[index] != ' ' && src[index] != '\r' && src[index] != '\n' && src[index] != '\t')
            {
                return src.substr(0, index + 1);
            }
        }

        return "";
    };

    static std::string Strip(const std::string &src)
    {
        string newString = Lstrip(src);
        return Rstrip(newString);
    };

    static std::vector<std::string> Split(const std::string &s, const std::string &separator)
    {
        vector<string> result;
        int pos;
        string temp = s;
        while ((pos = temp.find_first_of(separator)) != temp.npos)
        {
            if (pos > 0)
            {
                result.push_back(temp.substr(0, pos));
            }
            temp = temp.substr(pos + separator.length());
        }
        if (temp.length() > 0)
        {
            result.push_back(temp);
        }
        return std::move(result);
    };
};
#endif
