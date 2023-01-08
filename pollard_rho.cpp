#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

long long mulmod(long long a, long long b, long long m)
{
    unsigned long long a_ = (unsigned long long)a;
    unsigned long long b_ = (unsigned long long)b;
    unsigned long long m_ = (unsigned long long)m;
    unsigned long long r = 0;
    for (; b_>0; b_>>=1)
    {
        if (b_&1)
        {
            r += a_;
            if (r>=m_)
                r -= m_;
        }
        a_ += a_;
        if (a_>=m_)
            a_ -= m_;
    }

    return (long long)r;
}

long long powmod(long long a, long long b, long long m)
{
    long long r = 1;
    for (; b>0; b>>=1, a=mulmod(a, a, m))
        if (b&1)
            r = mulmod(r, a, m);
    return r;
}

bool is_prime(long long n)
{
    if (n==1)
        return false;
    if (n==2)
        return true;
    if (n%2==0)
        return false;

    long long d = n-1;
    long long s = 0;
    while (d%2==0)
    {
        d /= 2;
        s++;
    }

    // https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Testing_against_small_sets_of_bases
    long long A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (long long a: A)
    {
        if (a>=n)
            break;
        long long t = powmod(a, d, n);
        bool composite = t!=1;
        for (int i=0; i<s && composite; i++, t=mulmod(t, t, n))
            if (t==n-1)
                composite = false;
        if (composite)
            return false;
    }
    return true;
}

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

long long factor_f(long long x, long long n)
{
    return (mulmod(x, x, n)+1)%n;
}

long long factor_sub(long long n)
{
    if (n%2==0)
        return 2;
    if (is_prime(n))
        return n;

    for (long long i=2; ; i++)
    {
        long long x = i;
        long long y = factor_f(i, n); // i
        long long d = 1;
        while (d==1)
        {
            x = factor_f(x, n);
            y = factor_f(factor_f(y, n), n);
            d = gcd(abs(x-y), n);
        }
        if (d!=n)
            return d;
    }
}

vector<long long> factor(long long n)
{
    if (n==1)
        return {};

    long long f = factor_sub(n);
    if (f==n)
        return {n};

    vector<long long> F = factor(f);
    vector<long long> F2 = factor(n/f);
    F.insert(F.end(), F2.begin(), F2.end());
    sort(F.begin(), F.end());
    return F;
}

#include <iostream>

void print(vector<long long> F)
{
    bool first = true;
    for (long long f: F)
    {
        cout<<(first?"":" ")<<f;
        first = false;
    }
    cout<<endl;
}

int main()
{
    print(factor(1)); //
    print(factor(2)); // 2
    print(factor(3)); // 3
    print(factor(4)); // 2 2
    print(factor(5)); // 5
    print(factor(6)); // 2 3
    print(factor(0x7ffffffc80000005LL)); // 2147483647 4294967291
    print(factor(0x7fffffffffffffe7LL)); // 9223372036854775783
    print(factor(0x7fffffffffffffffLL)); // 7 7 73 127 337 92737 649657
}
