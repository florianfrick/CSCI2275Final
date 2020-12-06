#include "PriorityQueueHeap.h"

using namespace std;

PriorityQueueHeap::PriorityQueueHeap(int capa)
{
    if(capa >= 0)
    {
        capacity = capa;
    }
    currentSize = 0;
    heap = new heapItem*[capacity];
}

//Uses name and cost arrays to determine priority of the new item
void PriorityQueueHeap::push(string purchaser, product prod, vector<string> *prodNames, vector<int> *prodCosts, int arrSize)
{
    heapItem *newPurchase = new heapItem(purchaser, prod, -1);
    newPurchase->determinePriority(prodNames, prodCosts, arrSize);
    
    // Output for Debug Purposes
    // cout << "Added:  ";
    // newPurchase->print();

    if (currentSize == capacity)
    {
        std::cout << "Can not add item: heap full.";
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
    if(currentSize <= 0)
    {
        std::cout << "Can not remove item: heap empty.";
        return NULL;
    }
    if (currentSize == 1)
    {
        currentSize--;

        // Output for Debug Purposes
        // cout<< "Removed:  ";
        // heap[1]->print();

        return heap[1];
    }

    heapItem* popVal = heap[1];
    heap[1] = heap[currentSize];
    currentSize--;
    maxHeapify(1);

    // Output for Debug Purposes
    // cout<< "Removed:  ";
    // popVal->print();

    return popVal;
}

bool PriorityQueueHeap::empty()
{
    return currentSize <= 0;
}

heapItem* PriorityQueueHeap::get(int index)
{
    if(currentSize >= index)
    {
        return heap[index];
    }
    return NULL;
}

//prints the status of the entire underlying array. Bugfixing purposes only.
void PriorityQueueHeap::print()
{
    for(int i = 1; i < capacity; i++)
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