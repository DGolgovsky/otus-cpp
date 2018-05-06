#pragma once

#include "storage.h"

#include <cstddef>

namespace async
{
    using handle_t = void*;

    handle_t connect(std::size_t bulk)
    {
        return storage::instance().create(bulk);
    }
    void receive(handle_t handle, const char *data, std::size_t size)
    {
        static_cast<handle*>(handle)->process_data(data, size);
    }
    void disconnect(handle_t handle)
    {
        storage::instance().destroy(static_cast<handle *>(handle)->id());
    }
}
