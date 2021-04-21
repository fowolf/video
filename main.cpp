#include <iostream>
#include "include/OpenCvUtils.h"
#include "include/restclient-cpp/restclient.h"
#include "jsoncpp/json/json.h"

using  namespace RestClient;

int main() {
    std::cout << "Hello, World!" << std::endl;

    RestClient::Response res = RestClient::get("https://www.baidu.com/sugrec?prod=pc_his&from=pc_web&json=1&sid=33801_33815_33692_33848_33757_33915_26350_33811&hisdata=%5B%7B%22time%22%3A1618914212%2C%22kw%22%3A%22%E6%97%85%E5%AE%A2%E5%90%91%E9%A3%9E%E6%9C%BA%E6%89%94%E7%A1%AC%E5%B8%81%E7%A5%88%E7%A6%8F%E8%87%B4%E8%88%AA%E7%8F%AD%E5%8F%96%E6%B6%88%22%7D%2C%7B%22time%22%3A1618914346%2C%22kw%22%3A%22c%2B%2B%20http%22%7D%2C%7B%22time%22%3A1618915093%2C%22kw%22%3A%22libcurl%E5%AE%89%E8%A3%85%22%7D%2C%7B%22time%22%3A1618915339%2C%22kw%22%3A%22libcurl%E5%AE%89%E8%A3%85%E5%91%BD%E4%BB%A4%22%7D%2C%7B%22time%22%3A1618915382%2C%22kw%22%3A%22libcurl%20apt%22%7D%2C%7B%22time%22%3A1618915700%2C%22kw%22%3A%22libcurl3%E5%92%8C4%22%7D%2C%7B%22time%22%3A1618969081%2C%22kw%22%3A%22c%2B%2B%20libcurl%20%E5%B0%81%E8%A3%85%22%7D%2C%7B%22time%22%3A1618970082%2C%22kw%22%3A%22c%2B%2B%20libcurl%20%E5%B0%81%E8%A3%85%20linux%22%2C%22fq%22%3A2%7D%2C%7B%22time%22%3A1618970183%2C%22kw%22%3A%22%E4%B8%AD%E5%9B%BD%E5%9B%BD%E7%94%BB%E9%99%A220%E5%A5%97%E8%BF%9D%E5%BB%BA%E5%88%AB%E5%A2%85%E8%A2%AB%E6%B2%A1%E6%94%B6%22%7D%2C%7B%22time%22%3A1618971433%2C%22kw%22%3A%22deepin%20cmake%20%E5%8D%87%E7%BA%A7%22%7D%5D&_t=1618972576930&req=2&csor=0");
    Json::Value root;
    std::istringstream str(res.body);
    str >> root;
    std::cout << root.toStyledString() << std::endl;

//    OpenCvUtils openCvUtils = OpenCvUtils();
//    openCvUtils.OpencvUsb(0, 1920, 1080, 20);
//    openCvUtils.OpencvRtsp("rtsp://admin:xyab1234@172.29.144.48/h264/ch2/main/av_stream", 1920, 1080, 20);

    return 0;
}
