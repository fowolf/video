
#ifndef _VIDEO_CTIMEUTILS_H
#define _VIDEO_CTIMEUTILS_H

using namespace std;

class CTimeUtils
{
public:
    static std::string ToString(time_t &t, const std::string &);
    static time_t ToTime(std::string &, const std::string &);
};

#endif // _VIDEO_CTIMEUTILS_H
