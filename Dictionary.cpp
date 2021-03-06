#include "Dictionary.h"

using namespace std;

// Constructor that sets the dictionary's capacity.
Dictionary::Dictionary(int capacity)
{
    purchases = new vector<tuple<string, vector<Product>>>[capacity];
    hashSize = capacity;
}

// Returns a vector of all the products a given customer has in the dictionary.
vector<Product> Dictionary::search(string name)
{
    int hashIndex = hash(name);
    vector<tuple<string, vector<Product>>> *temp = &purchases[hashIndex]; //chained vector of all people who's names collide
    for(int i = 0; i < temp->size(); i++)
    {
        if(get<0>((*temp)[i]) == name)
        {
            return get<1>((*temp)[i]);
        }
    }
    return {};
}

// Adds a product to the dictionary where the customer's name is the key, and the product is the value.
bool Dictionary::insert(string name, Product p)
{
    int hashIndex = hash(name);
    vector<tuple<string, vector<Product>>> *temp = &purchases[hashIndex]; //chained vector of all people who's names collide

    // First person to be hashed at this index
    if(temp->empty())
    {
        addFirstAtHashedIndex(name, p, temp);
        return true;
    }

    // Determine if new or past customer
    for(int i = 0; i < temp->size(); i++)
    {
        if(isPastCustomer(name, temp,i))
        {
            int prodIndex = productIndex(p, get<1>((*temp)[i]));
            if(prodIndex >= 0)
            {
                // Customer has purchased this product before
                get<1>((*temp)[i]).at(prodIndex).num += p.num;
            }
            else
            {
                get<1>((*temp)[i]).push_back(p);
            }
            return true;
        }
    }
    // new customer
    vector<Product> newCustomerProducts;
    newCustomerProducts.push_back(p);

    temp->push_back(make_tuple(name, newCustomerProducts));
    return true;
}

// Helper method to determine if a customer is already in the dictionary.
bool Dictionary::isPastCustomer(string name, vector<tuple<string, vector<Product>>> *temp, int i)
{
    return get<0>((*temp)[i]) == name;
}

// Helper method to determine index of a product name in a vector of products.
int Dictionary::productIndex(Product p, vector<Product> products)
{
    for(int i = 0; i < products.size(); i++)
    {
        if(p.productName == products.at(i).productName)
        {
            return i;
        }
    }
    return -1;
}

// Helper method to add a person and their products to the dictionary if no additional chaining is necessary.
void Dictionary::addFirstAtHashedIndex(string name, Product p, vector<tuple<string, vector<Product>>> *temp)
{
    vector<Product> newProducts;
    newProducts.push_back(p);
    temp->push_back(make_tuple(name, newProducts));
}

// The hashing function to determine index of a string in dictionary's array.
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

// Prints every customer and the products they have purchased.
void Dictionary::print()
{
    for(int i = 0; i < hashSize; i++)
    {
        for(tuple<string, vector<Product>> hashValue: purchases[i])
        {
            cout << get<0>(hashValue) << endl;
            for(Product p: get<1>(hashValue))
            {
                cout << "\t" << p.productName << " " << p.num << endl;
            }
        }
    }
}

// Returns total cost of all products of one customer according to a cost array.
int Dictionary::customerTotal(string name, vector<string> *prodNames, vector<int> *prodCosts)
{
    vector<Product> products = search(name);
    int sum = 0;
    for(int i = 0; i < products.size(); i++)
    {
        // Searches for product in arrays to multiply amount by cost of product
        int costIndex = getCostIndex(products[i], prodNames, prodCosts);
        if(costIndex >= 0)
        {
            sum += products[i].num * prodCosts->at(costIndex);
        }
    }
    return sum;
}

// Helper method to find index in the name and cost arrays of a given product.
int Dictionary::getCostIndex(Product Product, vector<string> *prodNames, vector<int> *prodCosts)
{
    int costIndex = -1;
    for(int j = 0; j < prodNames->size(); j++)
    {
        if(prodNames->at(j) == Product.productName)
        {
            costIndex = j;
            break;
        }
    }
    return costIndex;
}

// Returns total cost of all products in the dictionary according to a cost array.
int Dictionary::total(vector<string> *prodNames, vector<int> *prodCosts)
{
    int sum = 0;
    for(int i = 0; i < hashSize; i++)
    {
        for(tuple<string, vector<Product>> hashValue: purchases[i])
        {
            sum += customerTotal(get<0>(hashValue), prodNames, prodCosts);
        }
    }
    return sum;
}

// Returns number of people in dictionary.
int Dictionary::count()
{
    int count = 0;
    for(int i = 0; i < hashSize; i++)
    {
        count += purchases[i].size();
    }
    return count;
}

// Determines if name of product p is in the vector of product names.
bool Dictionary::isProduct(Product p, vector<string> *prodNames)
{
    for(int i = 0; i < prodNames->size(); i++)
    {
        if(p.productName == prodNames->at(i))
        {
            return true;
        }
    }
    return false;
}