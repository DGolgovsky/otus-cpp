//
// Created by dmitry on 12/25/17.
//

#include "shared_ptr_alloc.h"

#include <iostream>
#include <memory>
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
    void *p=malloc(size);
    std::cout << "operator new: size = " << size << " p = " << p << std::endl;
    return p;
}

void operator delete (void* p)
{
    std::cout << "operator delete: p = " << p << std::endl;
    free(p);
}

template <class T>
struct custom_allocator {
    typedef T value_type;
    custom_allocator() noexcept {}
    template <class U> custom_allocator (const custom_allocator<U>&) noexcept {
        std::cout << "custom_allocator<T>::custom_allocator(const custom_allocator<U>&): "
                  << "\n\tT: " << get_class_name<T>()
                  << "\n\tU: " << get_class_name<U>() << std::endl;
    }
    T* allocate (std::size_t n) {

        std::cout << "Allocating: " << get_class_name<T>() << std::endl;
        return reinterpret_cast<T*>( ::operator new(n*sizeof(T)));
    }
    void deallocate (T* p, std::size_t n) {
        std::cout << "Deallocating: " << get_class_name<T>() << std::endl;
        ::operator delete(p);
    }


};

template <class T, class U>
constexpr bool operator== (const custom_allocator<T>&, const custom_allocator<U>&) noexcept
{
    std::cout << "operator== (const custom_allocator<T>&, const custom_allocator<U>&) "
              << "\n\tT: " << get_class_name<T>()
              << "\n\tU: " << get_class_name<U>() << std::endl;
    return true;
}

template <class T, class U>
constexpr bool operator!= (const custom_allocator<T>&, const custom_allocator<U>&) noexcept
{
    std::cout << "operator!= (const custom_allocator<T>&, const custom_allocator<U>&) "
              << "\n\tT: " << get_class_name<T>()
              << "\n\tU: " << get_class_name<U>() << std::endl;
    return false;
}

#pragma pack(push, 1)
struct foo_struct
{
    foo_struct()
    {
        std::cout << "foo_struct()" << std::endl;
    }

    ~foo_struct()
    {
        std::cout << "~foo_struct()" << std::endl;
    }
    uint64_t value1 = 1;
    uint64_t value2 = 2;
    uint64_t value3 = 3;
    uint64_t value4 = 4;
};
#pragma pack(pop)

void testAllocateShared()
{
    using control_block_type = std::_Sp_counted_ptr_inplace<foo_struct, custom_allocator<foo_struct>, (__gnu_cxx::_Lock_policy)2>;
    std::cout << "sizeof control_block_type: " << sizeof(control_block_type) << std::endl;
    std::cout << "sizeof foo_struct: " << sizeof(foo_struct) << std::endl;

    custom_allocator<foo_struct > alloc;
    auto foo = std::allocate_shared<foo_struct> (alloc);
}

void testMakeShared()
{
    auto foo = std::make_shared<foo_struct> ();
}
void testConstructShared()
{
    auto foo = std::shared_ptr<foo_struct> (new foo_struct);
}

int main() {

    std::cout << "---- Construct shared ----" << std::endl;
    testConstructShared();
    std::cout << "---- Construct shared ----" << std::endl;

    std::cout << "---- Make shared ----" << std::endl;
    testMakeShared();
    std::cout << "---- Make shared ----" << std::endl;

    std::cout << "---- Allocate shared ----" << std::endl;
    testAllocateShared();
    std::cout << "---- Allocate shared ----" << std::endl;
    return 0;
}