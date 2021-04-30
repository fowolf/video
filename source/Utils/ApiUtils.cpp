//
// Created by myuserid on 2021/4/22.
//

#include <sstream>
#include <iostream>
#include "ApiUtils.h"
#include "../include/restclient-cpp/restclient.h"
#include "jsoncpp/json/json.h"

vector<CameraConf> ApiUtils::GetCamList() {
    vector<CameraConf> rets = vector<CameraConf>();
    RestClient::Response res = RestClient::get(IRDCAMURL);
//    RestClient::Response res = RestClient::get("http://localhost:9000/irdcam");
    if (res.code != 200) {
        std::cout << "get error code: " << res.code << endl;
        return rets;
    }

    std::istringstream str(res.body);
    string body = str.str();
    std::cout << "body:" << body << endl;

    Json::Value root;
    Json::Reader reader;
    if (reader.parse(body, root)) {
        std::cout << root.toStyledString() << std::endl;
        if (!root.isMember("code") || root["code"].asInt() != 20000) {
            std::cout << "get code: " << root["code"].asInt() << " error" << endl;
            return vector<CameraConf>();
        }
        if (!root.isMember("result")) {
            std::cout << "can not find \"result\"" << std::endl;
            return vector<CameraConf>();
        }

        for (int i = 0; i < root["result"].size(); i++) {
            CameraConf cameraConf = {};
            if (root["result"][i].isMember("type")) {
                cameraConf.type = root["result"][i]["type"].asInt();
            }
            if (root["result"][i].isMember("link")) {
                cameraConf.link = root["result"][i]["link"].asInt();
            }
            if (root["result"][i].isMember("model")) {
                cameraConf.model = root["result"][i]["model"].asString();
            }
            if (root["result"][i].isMember("mac")) {
                cameraConf.mac = root["result"][i]["mac"].asCString();
            }
            if (root["result"][i].isMember("sn")) {
                cameraConf.sn = root["result"][i]["sn"].asCString();
            }
            if (root["result"][i].isMember("ip")) {
                cameraConf.ip = root["result"][i]["ip"].asCString();
            }
            if (root["result"][i].isMember("url")) {
                cameraConf.url = root["result"][i]["url"].asCString();
            }
            if (root["result"][i].isMember("tempIp")) {
                cameraConf.ip = root["result"][i]["tempIp"].asCString();
            }
            if (root["result"][i].isMember("tempPort")) {
                cameraConf.tempPort = root["result"][i]["tempPort"].asInt();
            }
            if (root["result"][i].isMember("video")) {
                cameraConf.video = vector<int>();
                for (const auto &v : root["result"][i]["video"]) {
                    cameraConf.video.push_back(v.asInt());
                }
            }
            if (root["result"][i].isMember("rtsp")) {
                cameraConf.rtsp = root["result"][i]["rtsp"].asCString();
            }
            rets.push_back(cameraConf);
        }
    }
    return rets;
}
