#include <vector>
#include <functional>
using namespace std;

vector<vector<int>> SCC(vector<vector<int>> E)
{
    int n = (int)E.size();

    vector<int> T;
    vector<bool> U(n);
    function<void(int)> f1 = [&](int c)
    {
        if (U[c])
            return;
        U[c] = true;
        for (int e: E[c])
            f1(e);
        T.push_back(c);
    };
    for (int c=0; c<n; c++)
        f1(c);

    vector<vector<int>> R(n);
    for (int i=0; i<n; i++)
        for (int e: E[i])
            R[e].push_back(i);

    vector<vector<int>> A;
    U = vector<bool>(n);
    function<void(int)> f2 = [&](int c)
    {
        if (U[c])
            return;
        U[c] = true;
        for (int e: R[c])
            f2(e);
        A.back().push_back(c);
    };
    for (int i=n-1; i>=0; i--)
        if (!U[T[i]])
        {
            A.push_back({});
            f2(T[i]);
        }
    return A;
}

#include <iostream>

int main()
{
    vector<vector<int>> A = SCC({
        {1},
        {2},
        {0, 3},
        {4},
        {3, 5, 6},
        {},
        {},
    });

    /*
     1 2 0
     4 3
     6
     5
    */
    for (vector<int> &a: A)
    {
        for (int x: a)
            cout<<" "<<x;
        cout<<endl;
    }
}
