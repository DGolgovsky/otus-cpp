#include "liballocator/allocator.h"
#include <map>
//#include "c_container.h"
#include "c_list.h"

/* NDEBUG */
/* */
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
/* */
/* NDEBUG */


template<class T>
class custom_allocator
{
private:
    T *ptr = nullptr;
    T *ptr_head = nullptr;

public:
    using value_type = T;

    custom_allocator() noexcept {
        std::cout << "Default constructor:" << "\n\tT: " << get_class_name<T>() << std::endl;
        allocate(10);
    }

    explicit custom_allocator(int n) noexcept {
        std::cout << "Single param constructor:" << "\n\tT: " << get_class_name<T>() << std::endl;
    }

    custom_allocator(const custom_allocator&) noexcept {
        std::cout << "Copy Constructor:" << "\n\tT: " << get_class_name<T>() << std::endl;
    }

    template<typename X>
    explicit custom_allocator(const custom_allocator<X> &other) noexcept {
        std::cout << "Construct T from X:" << "\n\tT: " << get_class_name<T>() << "\n\tX: " << get_class_name<X>() << std::endl;
    }

    T* allocate(std::size_t n) {
        if (!ptr_head) {
            ptr = reinterpret_cast<T*>(::operator new(n * sizeof(T)));
            ptr_head = ptr;
            std::cout << "\tAllocated:\n\t\t" << get_class_name<T>() << "\n\t\taddr: " << ptr << ", size: " << n << std::endl;
            return ptr;
        } else {
            return ptr++;
        }
    }

    void reserve(unsigned int size) {
        if (size)
            allocate(size);
    }

    template<class U>
    struct rebind {
        typedef custom_allocator<U> other;
    };

    void deallocate(T *p, std::size_t) {
        if (p == ptr_head) {// if there's a pool, nothing to do
            //std::cout << "\tDeallocating:\n\tT: " << get_class_name<T>() << ", addr: " << p << std::endl;
            ::operator delete(ptr_head);
            ptr_head = nullptr;
        }
    }

    template <typename U, typename ... Args>
    void construct(U* p, Args&& ... args) {
        //std::cout << "\tConstruct: " << p << std::endl;
        new (p) U(std::forward<Args>(args)...);
    }

    void destroy(T* p) {
        //std::cout << "\tDestroy: " << std::endl;
        p->~T();
    }
};

template <typename T>
void fill_container(T &cont)
{
    auto next = 1;
    cont.emplace(0, next);
    for (uint32_t i = 1; i != 10; ++i) {
        next *= i;
        cont.emplace(i, next);
    }
}

int main()
{
    {
        //std::cout << "std::map<std::allocator>\n";
        auto std_map = std::map<uint32_t, uint32_t>{};
        fill_container(std_map);
    }
    {
        //std::cout << "\nstd::map<custom::allocator>\n";
        auto custom_map = std::map<uint32_t, uint32_t, std::less<>, custom_allocator<std::pair<const uint32_t, uint32_t>>>{};
        //custom_map.get_allocator().reserve(10);
        fill_container(custom_map);

        for (auto const &it : custom_map) {
            std::cout << it.first << " " << it.second << std::endl;
        }
    }
    {
        std::cout << "\ncustom::list<std::allocator>\n";
        auto custom_list = c_list<uint32_t>{};
        fill_container(custom_list);
    }
    {
        std::cout << "\ncustom::list<custom::allocator>\n";
        auto custom_list = c_list<uint32_t, custom_allocator<Node<uint32_t>>>{};
        fill_container(custom_list);

        for(auto it : custom_list) {
            std::cout << it << std::endl;
        }
    }

    return 0;
}

