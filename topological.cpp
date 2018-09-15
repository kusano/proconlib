#include <vector>

using namespace std;

//  https://ja.wikipedia.org/wiki/トポロジカルソート
vector<int> topological(vector<vector<int>> E)
{
    int n = (int)E.size();
    
    vector<int> C(n);
    for (int i=0; i<n; i++)
        for (int e: E[i])
            C[e]++;

    vector<int> V;
    vector<int> S;
    for (int i=0; i<n; i++)
        if (C[i]==0)
            S.push_back(i);

    while (!S.empty())
    {
        int v = S.back();
        S.pop_back();
        V.push_back(v);
        for (int e: E[v])
            if (--C[e]==0)
                S.push_back(e);
    }

    return (int)V.size()==n ? V : vector<int>();
}

#include <iostream>

int main()
{
    vector<vector<int>> E =
    {
        {},
        {4, 6},
        {7},
        {4, 7},
        {5},
        {},
        {},
        {0, 5, 6},
    };

    vector<int> V = topological(E);
    //   3 2 7 0 1 6 4 5
    for (int v: V)
        cout<<" "<<v;
    cout<<endl;

    E[6].push_back(3);
    V = topological(E);
    //  0 (error)
    cout<<V.size()<<endl;
}
