#ifndef HEAP_H
#define HEAP_H

#include<vector>
#include<iostream>

struct dictItem
{
    public:
        std::string name;
        int priority;

        //constructor
        dictItem(std::string name, int priority)
            :name(name), priority(priority)
        {}
};


class Dictionary
{
    public:
        Dictionary(int capacity);
        bool empty();
        int size();
        int max_size();
        dictItem get(key k);
        bool insert(dictItem item);
        bool remove(key k);
        bool clear();
        int count(key k); //?
        bool contains(key k);
    private:

};

#endif // HEAP_H