#ifndef PQHEAP_H
#define PQHEAP_H

#include "product.cpp"
#include <string>
#include <vector>
#include<iostream>

class PriorityQueueHeap
{
    public:
        PriorityQueueHeap(int capacity);
        void push(std::string purchaser, product prod, vector<string> *prodNames, vector<int> *prodCosts, int arrSize);
        heapItem* pop();
        void print();
        bool empty();
        heapItem* get(int index);
    private:
        heapItem** heap; //array of pointers to heapItems
        int capacity;
        int currentSize;
        void maxHeapify(int i);
        void swap(int one, int two);
};

#endif // PQHEAP_H