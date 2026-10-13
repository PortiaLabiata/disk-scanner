#include <iostream>
#include <thread>
#include <filesystem>
#include "channel.hpp"
#include "worker.hpp"

int main(int argc, char **argv)
{
    prims::worker::channel_type channel;
    std::vector<prims::worker> workers;
    std::vector<std::thread> threads;

    std::filesystem::directory_iterator iter{".\\"};
    for (const auto& entry : iter)
    {
        if (entry.is_directory())
        {
            prims::worker worker{channel};
            prims::worker_functor func{worker, entry.path().string()};

            workers.push_back(worker); 
            threads.emplace_back(std::thread{func});
        }
    }

    while (true)
    {
        bool done = workers[0].done();
        for (std::size_t i = 1; i < workers.size(); i++)
        {
            done = done & workers[i].done();
            std::cout << workers[i].done() << std::endl;
        }

        if (done)
        {
            break;
        }

        auto data = channel.recv(); 
        for (const auto& entry : data)
        {
            std::cout << entry.filename << std::endl;
        }
    }

    return 0;
}
