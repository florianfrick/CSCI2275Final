#include <string>

class product
{
    public:
        std::string productName;
        int num;

    product(std::string pName, int n)
    {
        productName = pName;
        num = n;
    }
};