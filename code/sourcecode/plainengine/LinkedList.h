#pragma once

#include <iostream>
#include <stdexcept>

namespace plain
{
    template <typename T>
    class Node {
    public:
        T data;
        Node* next;

        Node(T data) {
            this->data = data;
            this->next = NULL;
        }
    };

    template <typename T>
    class LinkedList {
    private:
        Node<T>* head;

    public:
        LinkedList() {
            head = NULL;
        }

        ~LinkedList() {
            clear();
        }

        void insert(T data) {
            Node<T>* newNode = new Node<T>(data);
            if (!head) {
                head = newNode;
                return;
            } else {
                Node<T>* temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }

        void deleteNode(T key) {
            Node<T>* temp = head;
            Node<T>* prev = NULL;

            if (temp != NULL && temp->data == key) {
                head = temp->next; 
                delete temp;       
                return;
            }

            while (temp != NULL && temp->data != key) {
                prev = temp;
                temp = temp->next;
            }

            if (temp == NULL) return;

            prev->next = temp->next;

            delete temp;
        }

        int length() {
            int count = 0;
            Node<T>* temp = head;
            while (temp != NULL) {
                count++;
                temp = temp->next;
            }
            return count;
        }

        T& operator[](int index) {
            if (index < 0 || index >= length()) {
                throw std::out_of_range("Index out of range");
            }

            Node<T>* temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            return temp->data;
        }

        void clear() {
            Node<T>* current = head;
            Node<T>* nextNode;
            while (current != NULL) {
                nextNode = current->next;
                delete current;
                current = nextNode;
            }
            head = NULL;
        }
    };
}