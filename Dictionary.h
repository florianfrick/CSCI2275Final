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
        vector<Product> search(string name);
        bool insert(string name, Product Product);
        void print();
        int customerTotal(string name, vector<string> *prodNames, vector<int> *prodCosts);
        int total(vector<string> *prodNames, vector<int> *prodCosts);
        void addFirstAtHashedIndex(string name, Product p, vector<tuple<string, vector<Product>>> *temp);
        int count(); 
        int getCostIndex(Product Product, vector<string> *prodNames, vector<int> *prodCosts);
        bool isProduct(Product p, vector<string> *prodNames);
    private:
        int productIndex(Product p, vector<Product> products);
        bool isPastCustomer(string name, vector<tuple<string, vector<Product>>> *temp, int i);
        int hash(string name);

        int hashSize;
        vector<tuple<string, vector<Product>>> *purchases; // array of chaining vectors where each tuple represents a customer and their purchased products
};

#endif // HEAP_H