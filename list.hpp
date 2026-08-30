#ifndef LIST_H 
#define LIST_H
#include <iostream>
#include <string>

template <typename data_type>
struct Node {
    data_type node_data;
    Node<data_type>* next;
};

template <typename data_type>
class LinkedList
{
private:
    Node<data_type>* data;
    int length;

public:
    LinkedList(data_type* items, int count) {
        Node<data_type>* current_next = nullptr;
        for (int i = count - 1; i >= 0; --i) {
            current_next = new Node<data_type>{items[i], current_next};
        }
        data = current_next;
        length = count;
    }

    LinkedList () {
        length = 0;
        data = NULL;
    }

    LinkedList(LinkedList<data_type> &linkedList) {
        length = linkedList.GetLength();
        Node<data_type>* current_next = nullptr;
        for (int i = length - 1; i >= 0; --i) {
            current_next = new Node<data_type>{linkedList.Get(i), current_next};
        }
        data = current_next;
    }

    data_type GetFirst() {
        return data->node_data;
    }

    data_type Get(int index) {
        Node<data_type>* current = data;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->node_data;
    }

    data_type GetLast() {
        Node<data_type>* current = data;
        for (int i = 0; i < length - 1; i++) {
            current = current->next;
        }
        return current->node_data;
    }

    int GetLength() {
        return length;
    }

    void Prepend(data_type new_data) {
        Node<data_type>* new_head = nullptr;
        new_head = new Node<data_type>{new_data, data};
        data = new_head;
        length += 1;
    }

    void Append(data_type new_data) {
        Node<data_type>* new_end = nullptr;
        new_end = new Node<data_type>{new_data, NULL};
        if (data == NULL) {
            data = new_end;
        }
        else {
            Node<data_type>* current = data;
            for (int i = 0; i < length - 1; i++) {
                current = current->next;
            }
            current->next = new_end;
        }
        length += 1;
    }

    void InsertAt(data_type new_elem, int position) {
        if (data == NULL) {
            this->Append(new_elem);
        }
        else {
            Node<data_type>* current = data;
            Node<data_type>* new_node = nullptr;
            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }
            new_node = new Node<data_type>{new_elem, current->next};
            current->next = new_node;
            length += 1;
        }
    }

    void GetSubList(int startIndex, int endIndex) {
        Node<data_type>* current = data;
        Node<data_type>* previous = data;
        for (int i = 0; i < startIndex; i++) {
            current = current->next;
            delete previous;
            previous = current;
        }
        data = current;
        length = endIndex - startIndex;
        for (int i = startIndex; i < endIndex; i++) {
            current = current->next;
            previous = current;
        }
        for (int i = endIndex; i < length; i++) {
            current = current->next;
            previous = current;
            delete previous;
        }
    }

    //void Concat(LinkedList<data_type> *list) {
    //    int count = length - 1;
    //    length = length + list->GetLength();
    //    Node<data_type>* current = data;
    //    for (int i = 0; i < count; i++) {
    //        current = current->next;
    //    }
    //    current->next = list->data;
    //    list->data = nullptr;
    //    list->length = 0;
    //}

    ~LinkedList() {
        Node<data_type>* current = data;
        while (current != nullptr) {
            Node<data_type>* to_delete = current;
            current = current->next;
            delete to_delete;
        }
    }
};

#endif