#include "Dictionary.h"
#include "PriorityQueueHeap.h"
#include <fstream>
#include <sstream>

using namespace std;

// Creates arrays of product names, costs, and stock from external file. Returns size of arrays.
int createCostStock(string fileName, vector<string> *prodNames, vector<int> *prodStocks, vector<int> *prodCosts)
{
    ifstream productsFile;
    productsFile.open(fileName);
    if(!productsFile)
    {
        cout << "Error: Could not open products file." << endl;
        return -1;
    }

    string line;
    int i = 0;
    while(getline(productsFile, line))
    {
        //collects information from external file
        stringstream linestream(line);
        string prodName, prodStock, prodCost;
        getline(linestream, prodName, ',');
        getline(linestream, prodStock, ',');
        getline(linestream, prodCost, ',');

        //puts information into arrays
        prodNames->push_back(prodName);
        prodStocks->push_back(stoi(prodStock));
        prodCosts->push_back(stoi(prodCost));

        i++;
    }

    productsFile.close(); // closes the file
    return i;
}

// Returns number of lines in the file
int getNumLines(string fileName)
{
    ifstream file;
    file.open(fileName);
    if(!file)
    {
        cout << "Error: Could not open file." << endl;
        return -1;
    }
    int count = 0;
    string line;
    while(getline(file, line))
    {
        count++;
    }
    return count;
}

// Creates and returns Priority Queue Heap of orders from external file.
PriorityQueueHeap createOrders(string fileName, vector<string> *prodNames, vector<int> *prodCosts, int productsArrSize)
{
    int numOrders = getNumLines(fileName);
    ifstream ordersFile;
    ordersFile.open(fileName);
    
    PriorityQueueHeap ordersHeap = PriorityQueueHeap(numOrders); // Creates heap of capacity numOrders

    string line;
    while(getline(ordersFile, line))
    {
        // Collects information from external file
        stringstream linestream(line);
        string purchaser, prodName, prodAmount;
        getline(linestream, purchaser, ',');
        getline(linestream, prodName, ',');
        getline(linestream, prodAmount, ',');

        // Adds order to heap.
        ordersHeap.push(purchaser, product(prodName, stoi(prodAmount)), prodNames, prodCosts, productsArrSize);
    }

    ordersFile.close(); // closes the file
    return ordersHeap;
}

// Creates and returns dictionary by popping values from ordersHeap and using arrays to determine if product is in stock and the cost of the order. If an order is not in stock, prints message to console.
Dictionary fulfillOrders(PriorityQueueHeap *ordersHeap, vector<string> *prodNames, vector<int> *prodStocks, vector<int> *prodCosts)
{
    Dictionary tabs = Dictionary(1000);

    while(!ordersHeap->empty())
    {
        // Removes order from heap.
        heapItem *poppedOrder = ordersHeap->pop();
        if(poppedOrder != NULL)
        {
            // Adds order to dictionary under purchaser's "tab".
            tabs.insert(poppedOrder->purchaser, poppedOrder->prod);
        }
    }

    return tabs;
}

int main(int argc, char *argv[])
{
    // CREATE NAME, COST, AND STOCK ARRAYS
    vector<string> prodNames;
    vector<int> prodStocks;
    vector<int> prodCosts;
    int productsArrSize = createCostStock(argv[1], &prodNames, &prodStocks, &prodCosts);
    if(productsArrSize < 0)
    {
        return 0;
    }

    // CREATE PRIORITY QUEUE OF ORDERS
    PriorityQueueHeap ordersHeap = createOrders(argv[2], &prodNames, &prodCosts, productsArrSize);

    // FULFULL ORDERS
    Dictionary tabs = fulfillOrders(&ordersHeap, &prodNames, &prodStocks, &prodCosts);

    // OUTPUT
    tabs.print();

    cout << endl << "Total Cost: " << tabs.total(&prodNames, &prodCosts) << endl;
    cout << "Number of Customers: " << tabs.count() << endl;

    return 0;
};