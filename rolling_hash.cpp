#include <vector>
#include <string>
using namespace std;

template<long long M>
struct RollingHashM
{
    long long base;
    // H[i]: hash(S[:i])
    vector<long long> H;
    // E[i]: base^i
    vector<long long> E;

    RollingHashM(string S, long long base)
        : base(base)
    {
        int n = (int)S.size();
        H.resize(n+1);
        E.resize(n+1);

        H[0] = 0;
        for (int i=1; i<=n; i++)
            H[i] = (H[i-1]*base+S[i-1])%M;
        E[0] = 1;
        for (int i=1; i<=n; i++)
            E[i] = (E[i-1]*base)%M;
    }

    // hash(S[l:r])
    long long hash(int l, int r) const
    {
        return (H[r]+M-H[l]*E[r-l]%M)%M;
    }
};

struct RollingHash
{
    RollingHashM<0x7fffffffLL> H0;
    RollingHashM<0x7fffffedLL> H1;

    RollingHash(string S, long long base=1234LL)
        : H0(S, base)
        , H1(S, base)
    {
    }

    // hash(S[l:r])
    long long hash(int l, int r) const
    {
        return H0.hash(l, r)<<32 | H1.hash(l, r);
    }
};

#include <iostream>

int main()
{
    RollingHash RH("abcdabce");
    cout<<(RH.hash(0, 3)==RH.hash(4, 7))<<endl; // 1
    cout<<(RH.hash(0, 4)==RH.hash(4, 8))<<endl; // 0
    cout<<RH.hash(5, 5)<<endl; // 0
}
