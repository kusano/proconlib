// https://github.com/kusano/proconlib/blob/master/modinv.cpp

#include <tuple>
using namespace std;

tuple<long long, long long, long long> exgcd(long long a, long long b)
{
    if (b==0)
        return {1, 0, a};
    auto [y, x, g] = exgcd(b, a%b);
    y -= a/b*x;
    return {x, y, g};
}

long long modinv(long long a, long long m)
{
    auto [x, y, g] = exgcd(a, m);
    if (g!=1)
        return 0;
    return (x+m)%m;
}

#include <iostream>

int main()
{
    cout<<modinv(2, 998244353)<<endl; // 499122177
}
