#pragma once

#include <iostream>
#include <stdexcept>

namespace Plain
{
    template <typename T>
    class Node {
    public:
        T data;
        Node* next;

        Node(T data) {
            this->data = data;
            this->next = nullptr;
        }
    };

    template <typename T>
    class LinkedList {
    private:
        Node<T>* head;

    public:
        LinkedList() {
            head = nullptr;
        }

        ~LinkedList() {
            clear();
        }

        void insert(T data) {
            Node<T>* newNode = new Node<T>(data);
            if (head == nullptr) {
                head = newNode;
            } else {
                Node<T>* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }

        void deleteNode(T key) {
            Node<T>* temp = head;
            Node<T>* prev = nullptr;

            if (temp != nullptr && temp->data == key) {
                head = temp->next; 
                delete temp;       
                return;
            }

            while (temp != nullptr && temp->data != key) {
                prev = temp;
                temp = temp->next;
            }

            if (temp == nullptr) return;

            prev->next = temp->next;

            delete temp;
        }

        int length() {
            int count = 0;
            Node<T>* temp = head;
            while (temp != nullptr) {
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
            while (current != nullptr) {
                nextNode = current->next;
                delete current;
                current = nextNode;
            }
            head = nullptr;
        }
        
        void display() {
            Node<T>* temp = head;
            while (temp != nullptr) {
                std::cout << temp->data << " -> ";
                temp = temp->next;
            }
            std::cout << "nullptr" << std::endl;
        }
    };
}