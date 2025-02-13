#include "DownloadThread.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "nlohmann/json.hpp"
#include <iostream>

void DownloadThread::operator()(CommonObjects& common) {
    while (!common.exit_flag) {
        std::unique_lock<std::mutex> lock(common.data_mutex);
        common.cv.wait(lock, [&] { return common.start_download || common.exit_flag; });

        if (common.exit_flag) break;

        std::cout << "Downloading from URL: " << common.url << std::endl;
        common.json_ready = false;
        common.error_message.clear(); 

        httplib::Client cli(common.url.substr(0, common.url.find('/', 8)));
        cli.set_connection_timeout(5);
        cli.set_read_timeout(5);

        std::string path = common.url.substr(common.url.find('/', 8));
        auto res = cli.Get(path.c_str());

        if (res) {
            if (res->status == 200) {
                common.raw_json_data = res->body;
                std::cout << "[INFO] Download successful, JSON data ready." << std::endl;
            }
            else {
                common.error_message = "HTTP Error: " + std::to_string(res->status);
                std::cerr << "[ERROR] HTTP Request Failed. Status: " << res->status << std::endl;
            }
        }
        else {
            common.error_message = "HTTP Request Failed: No response from server.";
            std::cerr << "[ERROR] HTTP Request Failed. No response received." << std::endl;
        }

        common.start_download = false;
        common.data_ready = true;
        common.cv.notify_one();
    }
}



void DownloadThread::SetUrl(const std::string& new_url) {
    _download_url = new_url;
}
