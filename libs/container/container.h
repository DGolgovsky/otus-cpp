#ifndef CONTAINER_H
#define CONTAINER_H

#include "node.h"
#include <memory>

template <typename T, typename Alloc = std::allocator<Node<T>>>
class container
{
private:
    Node<T>* m_head = nullptr;
    //auto m_head = std::make_unique<Node<T>>(nullptr);
    Node<T>* m_tail = nullptr;
    //auto m_tail = std::make_unique<Node<T>>(nullptr);
    Alloc allocator_;

    class Iterator {
    private:
        Node<T>* m_node{};

    public:
        explicit Iterator(Node<T>* node) : m_node( node ) {}

        bool operator==(const Iterator& other) const {
            return this == &other || m_node == other.m_node;
        }

        bool operator!=(const Iterator& other) const {
            return !operator==(other);
        }

        T operator*() const {
            if(m_node) {
                return m_node->m_t;
            }
            return T();
        }

        void operator++() {
            if(m_node) {
                m_node = m_node->m_next;
            }
        }
    };

public:
    container() : m_head(nullptr) {}

    ~container() {
        while(m_head) {
            remove();
        }
    }

    void emplace(T, const T &t) {
        if (auto node = allocator_.allocate(1)) {
            allocator_.construct(node, t);
            if (m_head) {
                m_tail->m_next = node;
            } else {
                m_head = node;
                node->m_next = nullptr;
            }
            m_tail = node;
        }
    }

    void remove() {
        if (m_head) {
            Node<T>* newHead = m_head->m_next;
            allocator_.destroy(m_head);
            allocator_.deallocate(m_head, 1);
            m_head = newHead;
        }
    }

    T head() const;

    Iterator begin() const {
        return Iterator(m_head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    size_t size() const {
        size_t s = 0;
        for(Iterator it = begin(); it != end(); ++it) {
            ++s;
        }
        return s;
    }
};

#endif // CONTAINER_H
