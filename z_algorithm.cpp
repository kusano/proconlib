#include <vector>
#include <string>
using namespace std;

//  Z[i] = |LCP(S, S[i:])|
//  https://snuke.hatenablog.com/entry/2014/12/03/214243
vector<int> z_algorithm(string S)
{
    int n = (int)S.size();
    vector<int> Z(n);
    Z[0] = n;
    int j = 0;
    for (int i=1; i<n;)
    {
        while (i+j<n && S[j]==S[i+j])
            j++;
        Z[i] = j;
        if (j==0)
        {
            i++;
            continue;
        }
        int k;
        for (k=1; i+k<n && k+Z[k]<j; k++)
            Z[i+k] = Z[k];
        i += k;
        j -= k;
    }
    return Z;
}

#include <iostream>

int main()
{
    vector<int> Z = z_algorithm("aaabaaaab");
    //  921034210
    for (int z: Z)
        cout<<z;
    cout<<endl;
}
