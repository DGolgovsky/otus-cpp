#ifndef C_LIST_H
#define C_LIST_H

#include "node.h"


template <typename T, typename Alloc = std::allocator<Node<T>>>
class c_list
{
private:
    // Голова односвязного списка
    Node<T>* m_head = nullptr;
    Node<T>* m_tail = nullptr;
    Alloc allocator_;


    // Класс итератора односвязного списка
    class Iterator {
    public:
        explicit Iterator( Node<T>* node ) : m_node( node ) { }

        // Проверка на равенство
        bool operator==( const Iterator& other ) const {
            if( this == &other ) {
                return true;
            }
            return m_node == other.m_node;
        }

        // Проверка на неравенство
        bool operator!=( const Iterator& other ) const {
            return !operator==( other );
        }

        // Получение значения текущего узла
        T operator*() const {
            if( m_node ) {
                return m_node->m_t;
            } // Иначе достигнут конец списка. Уместно возбудить исключение
            return T();
        }

        // Переход к следующему узлу
        void operator++() {
            if( m_node ) {
                m_node = m_node->m_next;
            } // Иначе достигнут конец списка. Уместно возбудить исключение
        }

    private:
        Node<T>* m_node{};
    };

public:
    c_list() : m_head( NULL ) {
    }

    ~c_list() {
        while( m_head ) {
            remove();
        }
    }

    // Добавление узла в список
    void emplace( int dummy, const T &t ) {
        // Создаем новый узел для значения
        // Не забудем проверить, что память удалось выделить
        if (auto node = allocator_.allocate(1)) {
            allocator_.construct(node, t);
            if (m_head) {
                m_tail->m_next = node;
            } else {

                // Новый узел сам становится головным элементом
                m_head = node;
                // Новый узел привязывается к старому головному элементу
                node->m_next = nullptr;
            }
            m_tail = node;
        }
    }

    // Удаление последнего добавленного узла из списка
    void remove() {
        if( m_head ) { // Если список не пуст:
            // Сохраняем указатель на второй узел, который станет новым головным элементом
            Node<T>* newHead = m_head->m_next;

            // Освобождаем память, выделенную для удаляемого головного элемента
            //delete m_head;

            allocator_.destroy(m_head);
            allocator_.deallocate(m_head, 1);
            // Назначаем новый головной элемент
            m_head = newHead;
        } // Иначе могли бы возбудить исключение
    }

    // Получить головной элемент списка
    T head() const;

    // Получить итератор на начало списка
    Iterator begin() const {
        // Итератор пойдет от головного элемента...
        return Iterator( m_head );
    }

    // Получить итератор на конец списка
    Iterator end() const {
        // ... и до упора, т.е. NULL
        return Iterator( nullptr );
    }

    // Получить размер списка
    size_t size() const {
        size_t s = 0;
        for( Iterator it = begin(); it != end(); ++it ) {
            ++s;
        }

        /*
        Но можно и без итераторов
        for( Node* n = m_head; n != NULL; n = n->m_next ) {
            ++s;
        }
        */

        return s;
    }


};

#endif // C_LIST_H
