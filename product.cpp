#ifndef PROD_H
#define PROD_H

#include <string>
#include <iostream>

using namespace std;

class product
{
    public:
        string productName;
        int num;

    product(string pName, int n)
        :productName(pName), num(n)
    {}
};

class heapItem
{
    public:
        string purchaser;
        product prod;
        int priority;

        heapItem(string purchaser, product prod, int priority)
            :purchaser(purchaser), prod(prod), priority(priority)
        {}
    
    // priority determined by cost of purchase
    int determinePriority()
    {
        priority = prod.num; // temporary

        //look up productName in array of prices

        return priority;
    }

    void print()
    {
        cout << purchaser << " " << priority << " " << prod.productName << " " <<  prod.num << endl;
    }
};

#endif // PROD_H