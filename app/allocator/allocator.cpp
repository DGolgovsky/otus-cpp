#include "liballocator/allocator.h"
#include <map>
#include <memory>
#include <list>
#include "c_list.h"

template<class T>
class custom_allocator
{
private:
    T *ptr;

public:
    using value_type = T;

    custom_allocator() throw() {
        printf("Alloc Constructor: %p %32s\n", this, typeid(T).name());
        allocate(12);
    }

    custom_allocator(const custom_allocator&) throw() {
        printf("Copy Constructor: %p %32s\n", this, typeid(T).name());
    }

    template<typename X>
    explicit custom_allocator(const custom_allocator<X>&) throw() {
        printf("Construct T from X: %p %32s %32s\n", this, typeid(T).name(), typeid(X).name());
    }

    T* allocate(std::size_t n) {
        //std::cout << "Allocate " << n << " ";
        printf("Allocate: SZ:%zu OBJ:%p T:%32s ADDR:", n, this, typeid(T).name());
        ptr = reinterpret_cast<T *>(::operator new(n * sizeof(T)));
        std::cout << ptr << std::endl;

        if (ptr)
            return ptr;
        else
            throw std::bad_alloc();
    }

    auto reserve(size_t i) {
        std::cout << "Reserve " << i << std::endl;
        allocate(i);
    }

    void deallocate(T *p, std::size_t n) {
        std::cout << "Deallocate " << n << " " << p << std::endl;
        ::operator delete(p);
    }

    template <typename U, typename ... Args>
    void construct(U* p, Args&& ... args) {
        std::cout << "Construct " << p << std::endl;
        new (p) U(std::forward<Args>(args)...);
    }

    void destroy(T* p) {
        p->~T();
        std::cout << "Destroy" << std::endl;
    }

    T *address(T& x) const {
        return const_cast<T*>(address(const_cast<T const &>(x)));
    }

    T const *address(T const &x) const {
        return std::allocator<T>().address(x);
    }
};

class list;

class list;

template <typename T>
void fill_container(T &cont)
{
    auto next = 1;
    cont.emplace(0, next);
    //cont.insert(std::make_pair(0, next));
    for (uint32_t i = 1; i != 10; ++i) {
        next *= i;
        cont.emplace(i, next);
        //cont.insert(std::make_pair(i, next));
    }
}

int main()
{
    std::cout << "std::map<std::allocator>\n";
    auto std_map = std::map<uint32_t, uint32_t>{};
    fill_container(std_map);

    std::cout << "std::map<custom::allocator>\n";
    auto custom_map = std::map<uint32_t, uint32_t, std::less<>, custom_allocator<std::pair<const uint32_t, uint32_t>>>{};
    //custom_map.get_allocator().reserve(10);
    fill_container(custom_map);

    for (auto const &it : custom_map) {
        std::cout << it.first << " " << it.second << std::endl;
    }

    std::cout << "custom::list<custom::allocator>\n";
    auto c_list = List<uint32_t, custom_allocator<uint32_t>>{};
    auto next = 1;
    c_list.append(next);
    for (uint32_t i = 1; i != 10; ++i) {
        next *= i;
        c_list.append(next);
    }
    for (auto const &it : c_list) {
        std::cout << it << std::endl;
    }

    //std::list l;
    return 0;
}


