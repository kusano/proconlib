template<class T>
int popcount(T n)
{
    int c = 0;
    for (; n>0; n>>=1)
        c += int(n&1);
    return c;
}

#include <iostream>

using namespace std;

int main()
{
    cout<<popcount(0x12345678)<<endl;           //  13
    cout<<popcount(0x123456789abcdefLL)<<endl;  //  32
};
