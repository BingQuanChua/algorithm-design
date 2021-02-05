#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include <iostream>
#include <iomanip>
using namespace std;

struct Node
{
    int info; // index of connected planet
    double weight; // weight of edge in between
    Node *next;
};

template <typename T>
class LinkedList 
{
    Node *start;

public:
    LinkedList()
    {
        start = NULL;
    }
    
    void insert(int &element, double &weight)
    {
        Node *newNode = new Node;
        newNode->info = element;
        newNode->weight = weight;
        newNode->next = start;
        start = newNode;
    }

    bool find(int &target) 
    {
        bool found = false;
        Node *ptr = start;
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
        Node *ptr = list.start;
        char characters[] = "ABCDEFGHIJ";
        while(ptr != NULL) 
        {
            os << characters[ptr->info] << ": " << setw(7) << ptr->weight << "   ";
            ptr = ptr->next;
        }
        return os;
    }
};

#endif