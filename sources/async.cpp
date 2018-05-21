#include "async.h"
#include "storage.h"

namespace async
{
    using handle_t = void*;

	handle_t connect(std::size_t bulk)
    {
        return storage::instance().create(bulk);
    }

    void receive(handle_t hndl, const char *data, std::size_t size)
    {
        static_cast<handle*>(hndl)->process_data(data, size);
    }

    void disconnect(handle_t hndl)
    {
        storage::instance().destroy(static_cast<handle *>(hndl)->id());
    }
}
