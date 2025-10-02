#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include "cpp-httplib/httplib.h"

class Download
{
public:
    void download(const std::string &host, const std::string &path, const std::function<void(const std::string &, const std::string &)> &callback_world_count)
    {
        std::cout << "线程：" << std::this_thread::get_id() << "开始下载" << std::endl;
        httplib::Client client(host);
        auto response = client.Get(path);
        if (response && response->status == 200)
        {
            callback_world_count(path, response->body);
        }
    }

    void start_download(const std::string &host, const std::string &path, const std::function<void(const std::string &, const std::string &)> &callback_world_count)
    {
        auto download_func = std::bind(&Download::download, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        std::thread thread(download_func, host, path, callback_world_count);
        thread.detach();
    }
};

int main()
{
    auto d = Download();
    auto word_count = [](const std::string &path, const std::string &result) -> void
    {
        std::cout << "下载完成，文件路径：" << path << "，文件内容：" << result.substr(0, 102) << "..." << std::endl;
    };

    d.start_download("http://127.0.0.1:8000", "/novel1.txt", word_count);
    d.start_download("http://127.0.0.1:8000", "/novel2.txt", word_count);
    d.start_download("http://127.0.0.1:8000", "/novel3.txt", word_count);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 10));
    return 0;
}