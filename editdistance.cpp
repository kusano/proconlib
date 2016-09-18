#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int editDistance(string a, string b)
{
    int n = int(a.size());
    int m = int(b.size());
    vector<int> T(n+1);
    for (int j=0; j<=n; j++)
        T[j] = j;
    for (int i=1; i<=m; i++)
    {
        vector<int> P(n+1);
        T.swap(P);
        T[0] = i;
        for (int j=1; j<=n; j++)
            T[j] = min(min(T[j-1]+1, P[j]+1), P[j-1]+int(a[j-1]!=b[i-1]));
    }
    return T[n];
}

#include <iostream>

int main()
{
    cout<<editDistance("kitten", "sitting")<<endl;  //  3
    cout<<editDistance("", "")<<endl;               //  0
    cout<<editDistance("a", "b")<<endl;             //  1
    cout<<editDistance("abcd", "")<<endl;           //  4
    cout<<editDistance("", "abcd")<<endl;           //  4
}
