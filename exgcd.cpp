#include <tuple>
using namespace std;

// returns {x, y, g}.
// s.t. a*x+b*y = gcd(a, b) = g.
tuple<long long, long long, long long> exgcd(long long a, long long b)
{
    if (b==0)
        return {1, 0, a};
    auto [y, x, g] = exgcd(b, a%b);
    y -= a/b*x;
    return {x, y, g};
}

#include <iostream>

int main()
{
    auto [x1, y1, g1] = exgcd(3, 5);
    cout<<x1<<" "<<y1<<" "<<g1<<endl; // 2 -1 1

    auto [x2, y2, g2] = exgcd(123, 456);
    cout<<x2<<" "<<y2<<" "<<g2<<endl; // -63 17 3
}
