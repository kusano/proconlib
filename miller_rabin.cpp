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

#include <iostream>
using namespace std;

int main()
{
    cout<<is_prime(0)<<endl; // 0
    cout<<is_prime(1)<<endl; // 0
    cout<<is_prime(2)<<endl; // 1
    cout<<is_prime(3)<<endl; // 1
    cout<<is_prime(4)<<endl; // 0
    cout<<is_prime(5)<<endl; // 1
    cout<<is_prime(0x7fffffffffffffe7LL)<<endl; // 1
    cout<<is_prime(0x7fffffffffffffffLL)<<endl; // 0
}
