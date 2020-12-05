#include "Dictionary.h"
#include "PriorityQueueHeap.h"

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


    cout << endl << endl;
    PriorityQueueHeap *h = new PriorityQueueHeap(9);

    for(int i = 4; i >= 0; i--)
    {
        h->push(names[i], product(productNames[i], i*2));
    }
    for(int i = 4; i < 9; i++)
    {
        h->push(names[i], product(productNames[i], i*2));
    }
    
    h->print();
    cout << endl;
    for(int i = 8; i > 0; i--)
    {
        cout << "Removed: ";
        h->pop()->print();
    }
    cout << endl;
    h->print();

    return 0;
};