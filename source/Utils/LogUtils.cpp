
#include <iostream>
#include <unistd.h>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>

#include "CLogUtils.h"

using namespace std;

// CLogUtils *CLogUtils::plog_ = NULL;
std::string CLogUtils::_logFileName = CSystemUtils::getDefaultLogPath();

// // 获取log指针
// CLogUtils &CLogUtils::getInstance()
// {
//     if (plog_ == NULL)
//     {
//         plog_ = new CLogUtils;
//     }

//     return *plog_;
// }

log4cpp::Category &CLogUtils::getCatInstance(std::string catName)
{

    log4cpp::Category *cat = log4cpp::Category::exists(catName);
    if (cat == NULL)
    {
        auto &tmp = log4cpp::Category::getInstance(catName);

        // 自定义输出格式
        log4cpp::PatternLayout *pattern_one = new log4cpp::PatternLayout;
        pattern_one->setConversionPattern(LOG4CPP_FORMAT);

        log4cpp::PatternLayout *pattern_two = new log4cpp::PatternLayout;
        pattern_two->setConversionPattern(LOG4CPP_FORMAT);

        // 获取屏幕输出
        log4cpp::OstreamAppender *os_appender = new log4cpp::OstreamAppender("osAppender", &std::cout);
        os_appender->setLayout(pattern_one);

        // std::string logName = catName + std::string("_CLogUtils.log");
        std::string logName = _logFileName;

        auto index = logName.find_last_of("/");
        auto dirName = logName.substr(0, index);

        if (0 != access(dirName.c_str(), 0))
        {
            printf("%s not exists create it\n", dirName.c_str());
            mkdir(dirName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }

        // 获取文件日志输出 （ 日志文件名:CLogUtils.txt )
        log4cpp::RollingFileAppender *file_appender = new log4cpp::RollingFileAppender(
            "CLogUtils", logName.c_str(), LOG4CPP_FILE_SIZE, LOG4CPP_FILE_BACKUP);
        file_appender->setLayout(pattern_two);

        // category_ref_ = log4cpp::Category::getRoot();

        tmp.setPriority(log4cpp::Priority::DEBUG);
        tmp.addAppender(os_appender);
        tmp.addAppender(file_appender);

        tmp.info("%s CLogUtils created!", catName.c_str());

        return tmp;
    }
    else
    {
        cat->info("%s CLogUtils use exists!", catName.c_str());
    }
    return *cat;
}

log4cpp::Category &CLogUtils::getDefaultLogger(std::string loggerName)
{
    auto &logger = CLogUtils::getCatInstance(loggerName);
    return logger;
}

// 销毁
void CLogUtils::destroy()
{
    auto cats = *log4cpp::Category::getCurrentCategories();

    // Set the Appenders
    cout << cats.size() << std::endl;
    for (auto it = cats.begin(); it != cats.end(); it++)
    {
        auto &cat = *(*it);

        cout << "cat name: " << cat.getName().c_str() << std::endl;
        cat.info("%s is destroy", cat.getName().c_str());

        // cat.
        // cat.shutdown();
    }
}

void CLogUtils::setLogFile(std::string logFilePath)
{
    auto index = logFilePath.find_last_of("/");
    auto dirName = logFilePath.substr(0, index);

    if (0 != access(dirName.c_str(), 0))
    {
        printf("%s not exists create it\n", dirName.c_str());
        mkdir(dirName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    _logFileName = logFilePath;
}

std::string CLogUtils::getLogFile()
{
    return _logFileName;
}

// 构造函数
CLogUtils::CLogUtils() : category_ref_(log4cpp::Category::getRoot())
{
    // 自定义输出格式
    log4cpp::PatternLayout *pattern_one = new log4cpp::PatternLayout;
    pattern_one->setConversionPattern("[%d]-[%c%p]-[%u] - %m%n");

    log4cpp::PatternLayout *pattern_two = new log4cpp::PatternLayout;
    pattern_two->setConversionPattern("[%d]-[%c%p]-[%u] - %m%n");

    // 获取屏幕输出
    log4cpp::OstreamAppender *os_appender = new log4cpp::OstreamAppender("osAppender", &std::cout);
    os_appender->setLayout(pattern_one);

    // 获取文件日志输出 （ 日志文件名:CLogUtils.txt )
    log4cpp::RollingFileAppender *file_appender = new log4cpp::RollingFileAppender(
        "CLogUtils", "CLogUtils.txt", 5 * 1024, 10);
    file_appender->setLayout(pattern_two);

    // category_ref_ = log4cpp::Category::getRoot();

    category_ref_.setPriority(log4cpp::Priority::DEBUG);
    category_ref_.addAppender(os_appender);
    category_ref_.addAppender(file_appender);

    category_ref_.info("CLogUtils created!");
}

// 设置优先级
void CLogUtils::setPriority(Priority priority)
{
    switch (priority)
    {
    case (ERROR):
        category_ref_.setPriority(log4cpp::Priority::ERROR);
        break;

    case (WARN):
        category_ref_.setPriority(log4cpp::Priority::WARN);
        break;

    case (INFO):
        category_ref_.setPriority(log4cpp::Priority::INFO);
        break;

    case (DEBUG):
        category_ref_.setPriority(log4cpp::Priority::DEBUG);
        break;

    default:
        category_ref_.setPriority(log4cpp::Priority::DEBUG);
        break;
    }
}

void CLogUtils::error(const char *msg)
{
    category_ref_.error(msg);
}

void CLogUtils::warn(const char *msg)
{
    category_ref_.warn(msg);
}

void CLogUtils::info(const char *msg)
{
    category_ref_.info(msg);
}

void CLogUtils::debug(const char *msg)
{
    category_ref_.debug(msg);
}
