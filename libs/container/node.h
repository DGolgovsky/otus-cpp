#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node
{
    Node() : m_next(nullptr) { }

    explicit Node(T const &t) : m_t(t), m_next(nullptr ) {}

    T m_t;

    Node* m_next;
};

#endif // NODE_H
