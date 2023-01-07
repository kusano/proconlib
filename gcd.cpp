template<class T>
T gcd(T a, T b)
{
    while (a > 0)
    {
        T t = a;
        a = b%a;
        b = t;
    }
    return b;
}

#include <iostream>

using namespace std;

int main()
{
    cout<<gcd(10, 6)<<endl;     //  2
    cout<<gcd(6, 15)<<endl;     //  3
}
