#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary(int capacity)
{
    purchases = new vector<tuple<string, vector<product>>>[capacity];
    hashSize = capacity;
}

vector<product> Dictionary::search(string name)
{
    int hashIndex = hash(name);
    vector<tuple<string, vector<product>>> *temp = &purchases[hashIndex]; //chained vector of all people who's names collide
    for(int i = 0; i < temp->size(); i++)
    {
        if(get<0>((*temp)[i]) == name)
        {
            return get<1>((*temp)[i]);
        }
    }
    return {};
}

bool Dictionary::insert(string name, product p)
{
    int hashIndex = hash(name);
    vector<tuple<string, vector<product>>> *temp = &purchases[hashIndex]; //chained vector of all people who's names collide

    // First person to be hashed at this index
    if(temp->empty())
    {
        vector<product> newProducts;
        newProducts.push_back(p);
        temp->push_back(make_tuple(name, newProducts));
        return true;
    }

    // Determine if new or past customer
    for(int i = 0; i < temp->size(); i++)
    {
        if(get<0>((*temp)[i]) == name)
        {
            // past customer
            get<1>((*temp)[i]).push_back(p);
            return true;
        }
    }

    // new customer
    vector<product> newCustomerProducts;
    newCustomerProducts.push_back(p);

    temp->push_back(make_tuple(name, newCustomerProducts));
    return true;
}

int Dictionary::hash(string name)
{
    int sum = 0;
    for(char &c: name)
    {
        sum = sum + c;
        return sum % hashSize;
    }
    return -1;
}

void Dictionary::print()
{
    for(int i = 0; i < hashSize; i++)
    {
        for(tuple<string, vector<product>> hashValue: purchases[i])
        {
            cout << get<0>(hashValue) << endl;
            for(product p: get<1>(hashValue))
            {
                cout << "\t" << p.productName << " " << p.num << endl;
            }
        }
    }
}