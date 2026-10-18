#ifndef TRIE_HPP
#define TRIE_HPP

#include <memory>
#include <string>
#include <vector>
#include "worker.hpp"

namespace prims
{

class node {
public:
    node(std::string name, std::size_t size) 
        : _payload(name, size) 
    {
    }

    bool insert(std::vector<std::string>& path)
    {
        for (auto iter = _children.begin(); iter != _children.begin(); iter++)
        {
            for (auto node : _children)
            {
                if (node->_payload.filename == path[0])
                {
                    
                }
            }
        }
    }

private:
    worker_data _payload;
    std::vector<node*> _children;
};

}

#endif
