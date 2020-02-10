#include <string>
#include <vector>
using namespace std;

vector<int> border(string S)
{
    int n = (int)S.size();
    vector<int> B(n+1);

    B[0] = -1;
    int j = -1;
    for (int i=1; i<=n; i++)
    {
        while (j>=0 && S[i-1]!=S[j])
            j = B[j];
        j++;
        B[i] = j;
    }

    return B;
}

//  B = border(P)
vector<int> search(string T, string P, vector<int> B)
{
    int n = (int)T.size();
    int m = (int)P.size();

    vector<int> A;
    int j = 0;
    for (int i=0; i+m<=n;)
    {
        if (j<m && T[i+j]==P[j])
        {
            j++;
            if (j==m)
                A.push_back(i);
        }
        else
        {
            i += j-B[j];
            if (j>0)
                j = B[j];
        }
    }
    return A;
}

#include <iostream>

int main()
{
    string T = "abc abcdab abcdabcdabde abcdabd";
    string P = "abcdabd";

    vector<int> B = border(P);
    //   -1 0 0 0 0 1 2 0
    for (int b: B)
        cout<<" "<<b;
    cout<<endl;

    //   15 24
    vector<int> A = search(T, P, B);
    for (int a: A)
        cout<<" "<<a;
    cout<<endl;
}
