#include "Dictionary.h"

using namespace std;

int main()
{

    string names[] = {"Dave", "Jim", "Bob", "Elizabeth", "Richard", "Gerald", "Joe", "Margaret", "Blaine"};
    string productNames[] = {"nails", "books", "tables", "chairs", "mugs", "speaker", "timber", "steel", "fridge"};

    Dictionary *dict = new Dictionary(5);
    dict->print();

    for(int i = 0; i < 9; i++)
    {
        dict->insert(names[i], product(productNames[i], i*2));
    }

    dict->insert(names[0], product(productNames[1], 50));
    dict->print();

    cout << endl;
    vector<product> ps = dict->search("Dave");
    for(product p: ps)
    {
        cout << p.productName << " " << p.num << endl;
    }

    return 0;
};