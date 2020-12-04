#ifndef HEAP_H
#define HEAP_H

#include<vector>
#include<iostream>

struct heapItem
{
    public:
        std::string name;
        int priority;

        //constructor
        heapItem(std::string name, int priority)
            :name(name), priority(priority)
        {}
};


class PriorityQueueHeap
{
    public:
        PriorityQueueHeap(int capacity);
        void push(heapItem *obj);
        heapItem* pop();
        void printHeap();
    private:
        heapItem** heap; //array of pointers to heapItems
        int capacity;
        int currentSize;
        void minHeapify(int i);
        void swap(int one, int two);
};

#endif // HEAP_H