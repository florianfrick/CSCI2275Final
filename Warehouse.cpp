#include "Dictionary.h"

using namespace std;

int main()
{

    string names[] = {"Dave", "Jim", "Bob"};
    string productNames[] = {"nails", "books", "tables", "chairs", "mugs"};

    Dictionary *dict = new Dictionary(5);

    // for(int i = 0; i < 3; i++)
    // {
    //     dict->insert(names[i], product(productNames[i], i*2));
    // }

    product *p = new product(productNames[0], 200);
    
    dict->insert("Dave", *p);

    // dict->print();

    return 0;
};