#ifndef PROD_H
#define PROD_H

#include <string>
#include <iostream>
#include <vector>

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
    int determinePriority(vector<string> *prodNames, vector<int> *prodCosts, int arrSize)
    {
        //finds index that matches this product
        int index = -1;
        for(int i = 0; i < arrSize; i++)
        {
            if((*prodNames)[i] == prod.productName)
            {
                index = i;
                break;
            }
        }

        if(index >= 0)
        {
            //multiplies purchased amount by cost of product
            priority = prod.num * (*prodCosts)[index];
        }
        return priority;
    }

    void print()
    {
        cout << purchaser << " " << priority << " " << prod.productName << " " <<  prod.num << endl;
    }
};

#endif // PROD_H