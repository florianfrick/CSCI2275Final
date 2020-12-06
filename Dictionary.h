#ifndef HEAP_H
#define HEAP_H

#include "product.cpp"
#include<vector>
#include <string>
#include <tuple>
#include<iostream>

using namespace std;

class Dictionary
{
    public:
        Dictionary(int capacity);
        vector<product> search(string name); // returns vector of products purchased by given customer
        bool insert(string name, product product);
        void print();
        int customerTotal(string name, vector<string> *prodNames, vector<int> *prodCosts);
        int total(vector<string> *prodNames, vector<int> *prodCosts);
        void addFirstAtHashedIndex(string name, product p, vector<tuple<string, vector<product>>> *temp);
        int count(); 
    private:
        bool isPastCustomer(string name, vector<tuple<string, vector<product>>> *temp, int i);
        int getCostIndex(product product, vector<string> *prodNames, vector<int> *prodCosts);
        int hash(string name);

        int hashSize;
        vector<tuple<string, vector<product>>> *purchases; // array of chaining vectors where each tuple represents a customer and their purchased products
};

#endif // HEAP_H