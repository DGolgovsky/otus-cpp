#ifndef C_LIST_H
#define C_LIST_H

#include <list>

template <typename T, typename _Alloc = std::allocator<T>>
class List : protected _List_base<T, _Alloc>
{
private:
    // Объявление структуры узла для использования в классе Iterator
    struct Node;

public:
    // Класс итератора односвязного списка
    class Iterator {
    public:
        Iterator( Node* node ) : m_node( node ) { }

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
        Node* m_node;
    };

public:
    List() : m_head( NULL ) {
    }

    ~List() {
        while( m_head ) {
            remove();
        }
    }

    // Добавление узла в список
    void append( const T &t ) {
        // Создаем новый узел для значения
        // Не забудем проверить, что память удалось выделить
        if( Node* node = new Node( t ) ) {
            // Новый узел привязывается к старому головному элементу
            node->m_next = m_head;

            // Новый узел сам становится головным элементом
            m_head = node;
        }
    }

    // Удаление последнего добавленного узла из списка
    void remove() {
        if( m_head ) { // Если список не пуст:
            // Сохраняем указатель на второй узел, который станет новым головным элементом
            Node* newHead = m_head->m_next;

            // Освобождаем память, выделенную для удаляемого головного элемента
            delete m_head;

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
        return Iterator( NULL );
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

private:
    // Структура узла односвязного списка
    struct Node {
        Node() : m_next( NULL ) { }

        Node( const T& t ) : m_t( t ), m_next( NULL ) { }

        // Значение узла
        T m_t;

        // Указатель на следующий узел
        Node* m_next;
    };

    // Голова односвязного списка
    Node* m_head;
};

#endif // C_LIST_H

