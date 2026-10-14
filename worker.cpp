#include <filesystem>
#include <iostream>
#include <memory>
#include "worker.hpp"

namespace prims
{

worker::worker(channel_type& chan) : _channel(chan)
{
    _done = std::make_shared<std::atomic<bool>>(false);
}

void worker::run(std::string root)
{
    _work(root); 
    *_done = true;
}

void worker::_work(std::string root)
{
    std::filesystem::directory_entry entry{root};
    if (!entry.is_directory())
    {
        return;
    }

    std::filesystem::directory_iterator iter{entry};
    for (const auto& file : iter)
    {
        if (file.is_directory())
        {
            _work(file.path().string());
        }
        else
        {
            worker_data data = {
                .filename = file.path().string(),
                .size = file.file_size(),
            };
            _channel.send(data);
        }
    }
}

}
