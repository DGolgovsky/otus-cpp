//
// Created by dmitry on 12/26/17.
//

#ifndef ALLOCATOR_NODE_H
#define ALLOCATOR_NODE_H

template <typename T>
struct Node {
    Node() : m_next( NULL ) { }

    Node( const T& t ) : m_t( t ), m_next( NULL ) { }

    // Значение узла
    T m_t;

    // Указатель на следующий узел
    Node* m_next;
};

#endif //ALLOCATOR_NODE_H
