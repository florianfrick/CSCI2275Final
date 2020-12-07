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
        // Collects information from external file
        stringstream linestream(line);
        string prodName, prodStock, prodCost;
        getline(linestream, prodName, ',');
        getline(linestream, prodStock, ',');
        getline(linestream, prodCost, ',');

        // Puts information into arrays
        prodNames->push_back(prodName);
        prodStocks->push_back(stoi(prodStock));
        prodCosts->push_back(stoi(prodCost));

        i++;
    }

    productsFile.close(); // Closes the file
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

    // Counts lines
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
        ordersHeap.push(purchaser, Product(prodName, stoi(prodAmount)), prodNames, prodCosts, productsArrSize);
    }

    ordersFile.close(); // closes the file
    return ordersHeap;
}

// Fills dictionary by popping values from ordersHeap and using arrays to determine if product is in stock and the cost of the order.
void fulfillOrders(Dictionary *tabs, PriorityQueueHeap *ordersHeap, vector<string> *prodNames, vector<int> *prodStocks, vector<int> *prodCosts)
{
        while(!ordersHeap->empty())
    {
        // Removes order from heap.
        heapItem *poppedOrder = ordersHeap->pop();
        if(poppedOrder != NULL && tabs->isProduct(poppedOrder->prod, prodNames))
        {
            int costIndex = tabs->getCostIndex(poppedOrder->prod, prodNames, prodCosts);
            int newStock = prodStocks->at(costIndex) - poppedOrder->prod.num;
                        
            if(newStock >= 0)
            {
                // Adds order to dictionary under purchaser's "tab" if the product was in stock. Reduces stock by order's size.
                tabs->insert(poppedOrder->purchaser, poppedOrder->prod);
                prodStocks->at(costIndex) = newStock;
            }
        }
        else
        {
            cout << "Product is not offered." << endl;
        }
        
    }
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
    Dictionary tabs = Dictionary(1000);
    fulfillOrders(&tabs, &ordersHeap, &prodNames, &prodStocks, &prodCosts);

    // OUTPUT DICTIONARY INFO
    tabs.print();
    cout << endl << "Total Cost: " << tabs.total(&prodNames, &prodCosts) << endl;
    cout << "Number of Customers: " << tabs.count() << endl;


string menu = "\n======Main Menu=====\n"
					"1. Print Dictionary\n"
                    "2. Print First Order\n"
					"3. Print Customer Info\n"
                    "4. Print Total Cost\n"
                    "5. Add Order\n"
                    "6. Fulfill Orders\n"
                    "7. Print Stock\n"
                    "8. Print Costs\n"
                    "9. Quit\n";

    cout << menu << endl;
    int choice;
    bool exit = false;
    while(cin >> choice)
    {
        cin.clear();
        cin.ignore();
        switch (choice)
        {
                case 1:
                {
                    // Print Dictionary
                    tabs.print();
                    cout << endl << "Total Cost: " << tabs.total(&prodNames, &prodCosts) << endl;
                    cout << "Number of Customers: " << tabs.count() << endl;
                    break;
                }
                case 2:
                {
                    // Print First Order
                    heapItem *firstOrder = ordersHeap.get(1);
                    if(firstOrder != NULL)
                    {
                        firstOrder->print();
                    }
                    else
                    {
                        cout << "No order." << endl;
                    }
                    
                    break;
                }
                case 3:
                {
                    // Print Customer Info (products) and customer toatl
                    string name = "";
                    cout << "What is the name of the customer?" << endl;
                    cin >> name;
                    vector<Product> customerProds = tabs.search(name);
                    for(int i = 0; i < customerProds.size(); i++)
                    {
                        cout << "\t" << customerProds.at(i).productName << " " << customerProds.at(i).num << endl;
                    }
                    cout << tabs.customerTotal(name, &prodNames, &prodCosts);
                    break;
                }
                case 4:
                {
                    // Print Total Cost
                    cout << endl << "Total Cost: " << tabs.total(&prodNames, &prodCosts) << endl;
                    break;
                }
                case 5:
                {
                    // Add Order
                    string name = "";
                    cout << "What is the name of the customer?" << endl;
                    cin >> name;
                    string prodName = "";
                    cout << "What is the name of the product?" << endl;
                    cin >> prodName;
                    string num = "";
                    cout << "How many of the product?" << endl;
                    cin >> num;
                    ordersHeap.push(name, Product(prodName, stoi(num)), &prodNames, &prodCosts, productsArrSize);
                    break;
                }
                case 6:
                {
                    // Fulfill Orders
                    fulfillOrders(&tabs, &ordersHeap, &prodNames, &prodStocks, &prodCosts);
                    break;
                }
                case 7:
                {
                    // Print Stock
                    for(int i = 0; i < productsArrSize; i++)
                    {
                        cout << prodNames[i] << " " << prodStocks[i] << endl;
                    }
                    break;
                }
                case 8:
                {
                    // Print Costs
                    for(int i = 0; i < productsArrSize; i++)
                    {
                        cout << prodNames[i] << " " << prodCosts[i] << endl;
                    }
                    break;
                }
                case 9:
                {
                    // Quit
                    exit = true;
                    return 0;
                }
        }
        if (exit)
        {
                return 0;
        }
            
        cout << menu << endl;
    }


    return 0;
};