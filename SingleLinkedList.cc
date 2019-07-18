#ifndef AB_SINGLE_LINKED_LIST
#define AB_SINGLE_LINKED_LIST

#include <stdlib.h>
#include <iostream>
#include "./Iterator.cc"
template<class T>
struct genericSLL {
    T value;
    struct genericSLL *next;
};

template<class T>
class SingleLinkedListIterator : public Iterator<T> {
    struct genericSLL<T> *cursor;
    int counter = 0;
    public:
    SingleLinkedListIterator(struct genericSLL<T> *from) {
        this->cursor = from;
    }
    T *next() {
        if (cursor == NULL)
            throw counter;
        T *ret = &cursor->value;
        this->cursor = this->cursor->next;
        counter++;
        return ret;
    }
};

template<class T>
class SingleLinkedList {
    private:
        genericSLL<T> **root;
        int length = 0;
        void freeNodes(struct genericSLL<T> *first) {
            if (first == NULL)
                return;
            freeNodes(first->next);
            free(first);
        }
    public:
        SingleLinkedList<T>() {
            this->root = (genericSLL<T>**)malloc(sizeof(struct genericSLL<T>*));
            *this->root = NULL;
            this->length = 0;
        }
        ~SingleLinkedList<T>() {
            freeNodes(*this->root);
        }
        int getLength() {
            return length;
        }
        void add(T v) {
            struct genericSLL<T> *node = (struct genericSLL<T>*)malloc(sizeof(struct genericSLL<T>));
            node->value = v;
            node->next = *this->root;
            *this->root = node;
            length++;
        }
        // Checker é uma função que verifica se está certo com o nó, por exemplo um asteroide com vida
        int gc(bool (*checker) (T v)) {
            int deleted = 0;
            struct genericSLL<T> *cur = *this->root, **from = this->root, *dummy = NULL;
            while (cur != NULL) {
                if (!checker(cur->value)) {
                    *from = cur->next;
                    free(cur);
                    cur = *from;
                    deleted++;
                    continue;
                }
                from = &cur->next;
                cur = *from;
            }
            return deleted;
        }
        void forEach(void (*callback) (T *v)) {
            struct genericSLL<T> *here = *this->root;
            while (here != NULL) {
                callback(&here->value);
                here = here->next;
            }
        }
        SingleLinkedListIterator<T> asIterator() {
            return SingleLinkedListIterator<T>(*this->root);
        }
};

#endif
