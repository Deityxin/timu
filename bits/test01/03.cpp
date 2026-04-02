#include <iostream>
#include <vector>
#include <string>
using namespace std;
template<typename T>
size_t SList<T>::size() const {
    size_t count = 0;
    for (Node<T>* p = m_head; p != nullptr; p = p->m_next)
        ++count;
    return count;
}
