#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <filesystem>
#include "channel.hpp"
#include "worker.hpp"

int main(int argc, char **argv)
{
    (void)argc; (void)argv;
    prims::worker::channel_type channel;
    std::vector<prims::worker_functor> functors;
    std::vector<std::thread> threads;

    std::filesystem::directory_iterator iter{".\\"};
    for (const auto& entry : iter)
    {
        if (entry.is_directory() && !entry.is_symlink())
        {
            prims::worker w{channel};
            prims::worker_functor func{std::move(w), entry.path().string()};
            functors.emplace_back(func);
        }
    }

    // Launch threads later to avoid dangling references
    // due to vector reallocations
    for (auto f : functors)
    {
        threads.emplace_back(f);
    }

    std::vector<prims::worker_data> output;
    std::chrono::milliseconds tout{10};
    while (true)
    {
        bool done = true;
        for (const auto& functor: functors)
        {
            done = done && functor->done();
        }

        if (done)
            break;

        auto v = channel.recv(tout);
        if (v.has_value())
        {
            std::cout << v->filename << std::endl;
            output.push_back(*v);
        }
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
