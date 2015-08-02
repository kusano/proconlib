//  a^b % m
long long powmod(long long a, long long b, long long m)
{
    long long r = 1;
    for (; b>0; b>>=1, a=a*a%m)
        if (b&1)
            r = r*a%m;
    return r;
}

#include <iostream>
using namespace std;

int main()
{
    cout<<powmod(2, 3, 5)<<endl;                        //  3
    cout<<powmod(1234, 1000000006, 1000000007)<<endl;   //  1
}
