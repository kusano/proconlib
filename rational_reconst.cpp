#include <iostream>
#include <utility>
using namespace std;

// https://github.com/catupper/RationalModConverter
// https://en.wikipedia.org/wiki/Rational_reconstruction_(mathematics)
pair<long long, long long> rational_reconst(long long n, long long m)
{
    typedef pair<long long, long long> rat;
    rat v = {m, 0};
    rat w = {n, 1};

    while (w.first*w.first*2>m)
    {
        long long q = v.first/w.first;
        rat z = {v.first-q*w.first, v.second-q*w.second};
        v = w;
        w = z;
    }
    if (w.second<0)
    {
        w.first *= -1;
        w.second *= -1;
    }
    return w;
}

ostream &operator<<(ostream &o, pair<long long, long long> r)
{
    o<<r.first<<"/"<<r.second;
    return o;
}

int main()
{
    // 1/2
    cout<<rational_reconst(499122177LL, 998244353LL)<<endl;
    // 3/1
    cout<<rational_reconst(3LL, 998244353LL)<<endl;
    // 1337/31337
    cout<<rational_reconst(660516216LL, 998244353LL)<<endl;
}
