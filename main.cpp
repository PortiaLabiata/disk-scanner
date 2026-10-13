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

    std::vector<prims::worker_data> output;
    std::size_t got_values = 0;
    while (true)
    {
        if (got_values == workers.size())
        {
            break;
        }

        for (const auto& v : channel.recv())
        {
            output.push_back(v);
        }
        got_values++;
    }

    for (auto& thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }

    for (const auto& result : output)
    {
        std::cout << result.filename << "\t" << result.size << std::endl;
    }

    return 0;
}
