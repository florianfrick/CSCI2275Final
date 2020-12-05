#include "PriorityQueueHeap.h"
#include <iostream>
#include <string>

using namespace std;

PriorityQueueHeap::PriorityQueueHeap(int capa)
{
    capacity = capa;
    currentSize = 0;
    heap = new heapItem*[capacity];
}

//add to heap, then move to correct position
void PriorityQueueHeap::push(string purchaser, product prod)
{
    heapItem *newPurchase = new heapItem(purchaser, prod, -1);
    newPurchase->determinePriority();
    if (currentSize == capacity)
    {
        std::cout << "full";
    }
    else
    {
        currentSize++;
        int i = currentSize;
        heap[i] = newPurchase;
        while(i > 1 && heap[i/2]->priority < heap[i]->priority)
        {
            swap(i,i/2); //swaps indexes
            i /= 2;
        }
    }
}

heapItem* PriorityQueueHeap::pop()
{
    if(currentSize==0)
    {
        std::cout << "empty";
        return NULL;
    }
    if (currentSize == 1)
    {
        currentSize--;
        return heap[1];
    }

    heapItem* popVal = heap[1];
    heap[1] = heap[currentSize];
    currentSize--;
    maxHeapify(1);
    return popVal;
}

void PriorityQueueHeap::print()
{
    for(int i = 0; i < capacity; i++)
    {
        if(heap[i] != NULL)
        {
            cout << i << ": ";
            heap[i]->print();
        }
    }
}

void PriorityQueueHeap::maxHeapify(int i)
{
    int left = 2*i;
    int right = 2*i+1;
    int largest = i;
    //sorts by priority and treatment
    if(left <= currentSize && heap[left]->priority > heap[largest]->priority)
        largest = left;

    if(right <= currentSize && heap[right]->priority > heap[largest]->priority)
        largest = right;

    if(largest != i)
    {
        swap(i, largest); //swaps indexes
        maxHeapify(largest);
    }
}

void PriorityQueueHeap::swap(int one, int two)
{
    heapItem* temp = heap[one];
    heap[one] = heap[two];
    heap[two] = temp;
}