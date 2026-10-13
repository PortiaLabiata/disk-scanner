#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <cstddef>
#include <mutex>
#include <condition_variable>
#include <optional>
#include <array>

namespace prims
{

template <typename T, std::size_t S>
class channel {
public:
    channel()
    {
        static_assert(S > 0, "Channel size must be non-zero!");
        for (auto &v : _values)
        {
            v.reset();
        }
        _left = _right = _size = 0;
    }

    bool send(const T& v)
    {
        {
            std::unique_lock lock(_mtx);
            if (_size >= S)
            {
                return false;
            }

            _values[_left] = v;
            _left = (_left + 1) % S;
            _size++;
        }
        _condvar.notify_all();
        return true;
    }

    bool send(const T&& v)
    {
        {
            std::unique_lock lock(_mtx);
            if (_size >= S)
            {
                return false;
            }

            _values[_left] = std::move(v);
            _left = (_left + 1) % S;
            _size++;
        }
        _condvar.notify_all();
        return true;
    }

    T recv()
    {
        {
            std::unique_lock lock(_mtx);

            _condvar.wait(lock, [this] { return _size > 0; } );

            T v = std::move(*_values[_right]);
            _values[_right].reset();
            _right = (_right + 1) % S;
            _size--;
            return v;
        }
    }
private:
    std::mutex _mtx;
    std::condition_variable _condvar;
    std::array<std::optional<T>, S> _values;
    std::size_t _left, _right, _size;
};

}

#endif
