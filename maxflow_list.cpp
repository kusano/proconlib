#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int maxflow(vector<vector<int>> E_, vector<vector<int>> F_, int s, int t)
{
    int n = (int)E_.size();

    vector<vector<int>> E(n), F(n), R(n);
    for (int i=0; i<n; i++)
    for (int j=0; j<(int)E_[i].size(); j++)
    {
        int v = E_[i][j];
        R[i].push_back(int(E[v].size()));
        R[v].push_back(int(E[i].size()));
        E[i].push_back(v);
        E[v].push_back(i);
        F[i].push_back(F_[i][j]);
        F[v].push_back(0);
    }
    vector<bool> U(n);
    function<int (int, int)> dfs = [&](int p, int f)
    {
        if (p==t)
            return f;
        U[p] = true;
        for (int i=0; i<(int)E[p].size(); i++)
        if (!U[E[p][i]] && F[p][i]>0)
        {
            int t = dfs(E[p][i], min(f, F[p][i]));
            if (t>0)
            {
                F[p][i] -= t;
                F[E[p][i]][R[p][i]] += t;
                return t;
            }
        }
        return 0;
    };
    
    int flow = 0;
    while (true)
    {
        for (int i=0; i<n; i++)
            U[i] = false;
        int f = dfs(s, 0x7fffffff);
        if (f==0)
            break;
        flow += f;
    }

    return flow;
}

#include <iostream>

int main()
{
    /*
    from to   cap
    -------------
     0    1   10
     0    2    2
     1    2    6
     1    3    6
     2    4    5
     3    2    3
     3    4    8
    */
    vector<vector<int>> E =
    {
        {1, 2},
        {2, 3},
        {4},
        {2, 4},
        {},
    };
    vector<vector<int>> F =
    {
        {10, 2},
        {6, 6},
        {5},
        {3, 8},
        {},
    };
    cout<<maxflow(E, F, 0, 4)<<endl;
}
