#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <iostream>

namespace alloc {
    template<class T, uint32_t reserve_size = 10>
    class custom_allocator
    {
    private:
        T *ptr = nullptr;
        T *ptr_head = nullptr;

    public:
        using value_type = T;

        custom_allocator() noexcept {
            if (reserve_size)
                allocate(reserve_size);
        }

        explicit custom_allocator(int n) noexcept {}

        template<typename X>
        explicit custom_allocator(const custom_allocator<X> &other) noexcept {}

        T *allocate(std::size_t n) {
            if (!ptr_head) {
                ptr = reinterpret_cast<T *>(::operator new(n * sizeof(T)));
                if (!ptr)
                    throw std::bad_alloc();
                ptr_head = ptr;
                return ptr;
            } else {
                return ptr++;
            }
        }

        void reserve(std::size_t size) {
            if (size)
                allocate(size);
        }

        template<class U>
        struct rebind {
            typedef custom_allocator<U> other;
        };

        void deallocate(T *p, std::size_t) {
            if (p == ptr_head) {// if there's not a pool, nothing to do
                ::operator delete(ptr_head);
                ptr_head = nullptr;
            }
        }

        template<typename U, typename ... Args>
        void construct(U *p, Args &&... args) {
            new(p) U(std::forward<Args>(args)...);
        }

        void destroy(T *p) {
            p->~T();
        }
    };
} // namespace alloc
#endif

