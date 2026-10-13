#include <filesystem>
#include <iostream>
#include "worker.hpp"

namespace prims
{

worker::worker(channel_type& chan) : _channel(chan)
{
}

void worker::run(std::string root)
{
    std::filesystem::directory_entry entry{root};
    if (!entry.is_directory())
    {
        return;
    }

    std::vector<worker_data> output;
    std::filesystem::directory_iterator iter{entry};
    for (const auto& file : iter)
    {
        worker_data data = {
            .filename = file.path().string(),
            .size = file.file_size(),
        };
        output.push_back(data);
    }

    _done = true;
    _channel.send(output);
}

}
