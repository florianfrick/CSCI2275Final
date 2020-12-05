#ifndef PQHEAP_H
#define PQHEAP_H

#include "product.cpp"
#include <string>
#include<iostream>

class PriorityQueueHeap
{
    public:
        PriorityQueueHeap(int capacity);
        void push(std::string purchaser, product prod);
        heapItem* pop();
        void print();
    private:
        heapItem** heap; //array of pointers to heapItems
        int capacity;
        int currentSize;
        void maxHeapify(int i);
        void swap(int one, int two);
};

#endif // PQHEAP_H