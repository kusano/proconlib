#include <vector>
using namespace std;

long long powmod(long long a, long long b, long long m)
{
    long long r = 1;
    for (; b>0; b>>=1, a=a*a%m)
        if (b&1)
            r = r*a%m;
    return r;
}

long long determinant_mod(vector<vector<long long>> A, long long M)
{
    int n = (int)A.size();
    long long d = 1;
    for (int i=0; i<n; i++)
    {
        if (A[i][i]==0)
        {
            for (int j=i+1; j<n; j++)
                if (A[j][i]!=0)
                {
                    A[i].swap(A[j]);
                    d = -d;
                    break;
                }
            if (A[i][i]==0)
                return 0;
        }

        for (int j=i+1; j<n; j++)
        {
            long long x = A[j][i]*powmod(A[i][i], M-2, M)%M;
            for (int k=i; k<n; k++)
                (A[j][k] += M-A[i][k]*x%M) %= M;
        }
    }

    d = powmod(d+M, M-2, M);
    for (int i=0; i<n; i++)
        d = d*A[i][i]%M;
    return d;
}

#include <iostream>

int main()
{
    cout<<determinant_mod({
        {2, 2},
        {3, 6},
    }, 1000000007)<<endl;
    // 6

    cout<<determinant_mod({
        {2, 2},
        {3, 6},
    }, 5)<<endl;
    // 1
}
