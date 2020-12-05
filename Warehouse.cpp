#include "Dictionary.h"
#include "PriorityQueueHeap.h"
#include <fstream>
#include <sstream>

using namespace std;

// Creates arrays of product names, costs, and stock. Returns size of arrays.
int costStock(string fileName, vector<string> *prodNames, vector<int> *prodStocks, vector<int> *prodCosts)
{
    ifstream productsFile;
    productsFile.open(fileName);
    if(!productsFile)
    {
        cout << "Error: Could not open file." << endl;
        return -1;
    }

    string line;
    int i = 0;
    while(getline(productsFile, line))
    {
        stringstream linestream(line);
        string prodName, prodStock, prodCost;
        
        //collects information from external file
        getline(linestream, prodName, ',');
        getline(linestream, prodStock, ',');
        getline(linestream, prodCost, ',');

        //puts information into arrays
        prodNames->push_back(prodName);
        prodStocks->push_back(stoi(prodStock));
        prodCosts->push_back(stoi(prodCost));
        i++;
    }

    productsFile.close();// close the file
    return i;
}

int main(int argc, char *argv[])
{
    // CREATE NAME, COST, AND STOCK ARRAYS
    vector<string> prodNames;
    vector<int> prodStocks;
    vector<int> prodCosts;
    int arrSize = costStock(argv[1], &prodNames, &prodStocks, &prodCosts);
    if(arrSize < 0)
    {
        return 0;
    }



    //DICTIONARY TEST
    string buyers[] = {"Dave", "Jim", "Bob", "Elizabeth", "Richard", "Gerald", "Joe", "Margaret", "Blaine"};

    Dictionary *dict = new Dictionary(5);
    // cout << "Dictionary:" << endl;
    // dict->print();

    // for(int i = 0; i < 9; i++)
    // {
    //     dict->insert(buyers[i], product(prodNames[i], i*2));
    // }

    // dict->insert(buyers[0], product(prodNames[1], 50));
    // dict->print();

    // cout << endl;
    // vector<product> ps = dict->search("Dave");
    // cout << "Searched for Dave:" << endl; 
    // for(product p: ps)
    // {
    //     cout << p.productName << " " << p.num << endl;
    // }

    //HEAP TEST
    cout << endl << "Heap:" << endl;
    PriorityQueueHeap *h = new PriorityQueueHeap(9);

    for(int i = 0; i < 9; i++)
    {
        h->push(buyers[i], product(prodNames[i], prodStocks[i]), &prodNames, &prodCosts, arrSize);
    }
    // for(int i = 4; i < 9; i++)
    // {
    //     h->push(names[i], product(prodNames[i], i*2), prodNames, prodCosts, arrSize);
    // }
    
    cout << endl << "Heap Created" << endl;
    h->print(); //causes program to exit
    cout << endl;
    for(int i = 0; i < 9; i++)
    {
        cout << "Removed: ";
        h->pop()->print();
    }
    cout << endl;
    h->print();


    return 0;
};