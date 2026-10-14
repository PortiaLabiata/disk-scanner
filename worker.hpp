#ifndef WORKER_HPP
#define WORKER_HPP

#include <memory>
#include <string>
#include <atomic>
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
        channel<worker_data, CHAN_SIZE>;

    worker(channel_type& chan);
    void run(std::string root);
    bool done() const { return *_done; }
private:
    void _work(std::string root);

    std::shared_ptr<std::atomic<bool>> _done;
    channel_type &_channel;
};

class worker_functor {
public:
    worker_functor(worker&& w, std::string root) 
        : _worker(std::make_shared<worker>(std::move(w))), _root(std::move(root)) {}

    worker_functor(const worker_functor& other)
        : _worker(other._worker),
          _root(other._root) {}

    void operator()() 
    {
        _worker->run(_root);
    }

    const worker *operator->() const
    {
        return _worker.get();
    }
private:
    std::shared_ptr<worker> _worker;
    std::string _root;
};

}

#endif
