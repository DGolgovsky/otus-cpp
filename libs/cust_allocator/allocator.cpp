#include "allocator.h"

#ifdef NDEBUG
#include <cxxabi.h>
template <class T>
const char* get_class_name()
{
    static int st = 0;
    size_t dlen = 0;
    static auto mangled = typeid(T).name();
    static char * demangled = abi::__cxa_demangle(mangled, demangled, &dlen, &st);
    return 0 == st ? demangled : mangled;
}
void* operator new (size_t size)
{
    void *p = std::malloc(size);
    std::cout << "operator new: size = " << size << " p = " << p << std::endl;
    return p;
}

void operator delete (void* p, std::size_t)
{
    std::cout << "operator delete: p = " << p << std::endl;
    std::free(p);
}
void operator delete (void* p)
{
    std::cout << "operator delete: p = " << p << std::endl;
    std::free(p);
}
#endif