#ifndef WORKER_HPP
#define WORKER_HPP

#include <string>
#include <utility>
#include <vector>
#include "channel.hpp"

namespace prims
{

struct worker_data {
    std::string filename;
    std::size_t size;
};

class worker {
public:
    static constexpr std::size_t CHAN_SIZE = 512;

    using channel_type = 
        channel<std::vector<worker_data>, CHAN_SIZE>;

    worker(channel_type& chan);
    void run(std::string root);
    bool done() { return _done; }
private:
    bool _done = false;
    channel_type &_channel;
};

class worker_functor {
public:
    worker_functor(worker& w, std::string root) 
        : _worker(w), _root(root) {}

    void operator()() 
    {
        _worker.run(_root);
    }
private:
    worker& _worker;
    std::string _root;
};

}

#endif
