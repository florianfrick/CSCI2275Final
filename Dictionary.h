#ifndef HEAP_H
#define HEAP_H

#include "product.cpp"
#include<vector>
#include <string>
#include <tuple>
#include<iostream>

using namespace std;

//generic dictionary class
//one array for products[string]
//one array for products's costs[int]
//one array for products's and their stock[int]
//one dictionary for customers[string] and their purchases[array of vectors of products]
//one array for purchased products[string] and the amount purchased[int]
class Dictionary
{
    public:
        Dictionary(int capacity);
        vector<product> search(string name); // returns vector of products purchased by given customer
        bool insert(string name, product product);
        int hash(string name);
        void print();

        bool remove(string name);
        bool empty();
        int size();
        int max_size();
        bool clear();
        int count(string name); //?
        bool contains(string name);
    private:
        int hashSize;
        vector<tuple<string, vector<product>>> *purchases; // array of chaining vectors where each tuple represents a customer and their purchased products
};

#endif // HEAP_H