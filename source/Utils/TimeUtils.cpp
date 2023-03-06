#include <iostream>
#include "CTimeUtils.h"

std::string CTimeUtils::ToString(time_t &t, const std::string &format)
{
    // time(&t);
    // printf("now:%ld \n", t);
    struct tm *tmp_time = localtime(&t);

    char s[100];
    strftime(s, sizeof(s), format.c_str(), tmp_time);
    // printf("%d: %s\n", (int)t, s);
    return std::string(s);
}

time_t CTimeUtils::ToTime(std::string &timeStr, const std::string &format)
{

    struct tm *tmp_time = (struct tm *)malloc(sizeof(struct tm));
    strptime(timeStr.c_str(), format.c_str(), tmp_time);

    time_t t = mktime(tmp_time); // 按当地时区解析tmp_time
    return t;
}

// int main()
// {

//     time_t now;

//     time(&now);

//     printf("now:%ld \n", now);

//     struct tm *tmp_time = localtime(&now);
//     char s[100];

//     strftime(s, sizeof(s), "%04Y-%02m-%02d %H:%M:%S", tmp_time);

//     printf("%d: %s\n", (int)now, s);

//     struct tm *tmp_time1 = (struct tm *)malloc(sizeof(struct tm));
//     strptime(s, "%04Y-%02m-%02d %H:%M:%S", tmp_time1);

//     time_t t = mktime(tmp_time1); // 按当地时区解析tmp_time

//     printf("%ld\n", t);

//     // free(tmp_time);
// }