#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include <iostream>
#include <iomanip>
using namespace std;

template <typename T>
struct Node
{
    T info;         // info
    double value;   // value, the value to be sorted and displayed
    Node<T> *next;
};

template <typename T>
class LinkedList 
{
    Node<T> *start;

public:
    LinkedList()
    {
        start = NULL;
    }
    
    void insert(T &element, double &value)
    {
        Node<T> *newNode = new Node<T>;
        newNode->info = element;
        newNode->value = value;
        newNode->next = start;
        start = newNode;
    }

    void splitLinkedList(Node<T> *head, Node<T> **a, Node<T> **b) {
        Node<T> *front;
        Node<T> *back;
        back = head;
        front = head->next;

        while (front != NULL) {
            front = front->next;
            if (front != NULL) {
                back = back->next;
                front = front->next;
            }
        }

        *a = head;
        *b = back->next;
        back->next = NULL;
    }
    
    Node<T> * merge(Node<T> *a, Node<T> *b, int order) {
        Node<T> *result = NULL;

        if (a == NULL) {
            return b;
        }
        else {
            if (b == NULL) {
                return a;
            }
        }

        if (order == 0) {
            if (a->value <= b->value) {
                result = a;
                result->next = merge(a->next, b, order);
            }
            else {
                result = b;
                result->next = merge(a, b->next, order);
            }
        }
        else {
            if (a->value <= b->value) {
                result = b;
                result->next = merge(a, b->next, order);
            }
            else {
                result = a;
                result->next = merge(a->next, b, order);
            }
        }
        
        return result;
    }

    void startMergeSort(int order=0) {
        // order: 0 => ascending
        // order: 1 => descending
        mergeSort(&start, order);
    }

    void mergeSort(Node<T> **start, int order) {
        Node<T> *head = *start;
        Node<T> *a; // first half
        Node<T> *b; // second half

        if((head == NULL) || (head->next == NULL)) {
            return;
        }

        splitLinkedList(head, &a, &b);
        mergeSort(&a, order);
        mergeSort(&b, order);

        *start = merge(a, b, order);
    }


    bool find(T target) 
    {
        bool found = false;
        Node<T> *ptr = start;
        while(ptr != NULL && !found) 
        {
            if(ptr->info == target)
            {
                found = true;
            }
            else 
            {
                ptr = ptr->next;
            }
        }
        return found;
    }

    bool isEmpty() 
    {
        if(start == NULL)
            return false;
        else
            return true;
    }

    // print single linked list when called
    friend ostream &operator<< (ostream &os, LinkedList<T> &list) 
    {
        Node<T> *ptr = list.start;
        while(ptr != NULL) 
        {
            os << ptr->info << ": " << setw(7) << ptr->value << " ";
            ptr = ptr->next;
            if (ptr != NULL) {
                os << "-> ";
            }
        }
        return os;
    }

};

#endif