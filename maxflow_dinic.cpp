#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

template<class T>
T maxflow(vector<vector<int>> E_, vector<vector<T>> C_, int s, int t)
{
    int n = (int)E_.size();
    vector<vector<int>> E(n), R(n);
    vector<vector<T>> C(n);
    T mx = {};
    for (int i=0; i<n; i++)
    for (int j=0; j<(int)E_[i].size(); j++)
    {
        int v = E_[i][j];
        R[i].push_back((int)E[v].size());
        R[v].push_back((int)E[i].size());
        E[i].push_back(v);
        E[v].push_back(i);
        C[i].push_back(C_[i][j]);
        C[v].push_back(T());
        mx = max(mx, C_[i][j]);
    }

    vector<int> D;
    vector<int> I;

    auto bfs = [&]()
    {
        D = vector<int>(n, -1);
        vector<int> Q;
        D[s] = 0;
        Q.push_back(s);
        int q = 0;
        while (q<(int)Q.size())
        {
            int v = Q[q++];
            for (int i=0; i<(int)E[v].size(); i++)
            if (C[v][i]>0 && D[E[v][i]]==-1)
            {
                D[E[v][i]] = D[v]+1;
                Q.push_back(E[v][i]);
            }
        }
    };

    function<T(int,T)> dfs = [&](int v, T f)
    {
        if (v==t)
            return f;
        for (int &i=I[v]; i<(int)E[v].size(); i++)
        if (C[v][i]>0 && D[v]<D[E[v][i]])
        {
            T d = dfs(E[v][i], min(f, C[v][i]));
            if (d>0)
            {
                C[v][i] -= d;
                C[E[v][i]][R[v][i]] += d;
                return d;
            }
        }
        return T();
    };

    T flow = {};
    while (true)
    {
        bfs();
        if (D[t]==-1)
            break;
        I = vector<int>(n, 0);
        while (true)
        {
            T f = dfs(s, mx);
            if (f == T())
                break;
            flow += f;
        }
    }
    return flow;
}

#include <iostream>

int main()
{
    /*
    from to   cap
    -------------
     0    1   10.0
     0    2    2.0
     1    2    6.0
     1    3    5.9
     2    4    5.0
     3    2    3.0
     3    4    8.0
    */
    vector<vector<int>> E =
    {
        {1, 2},
        {2, 3},
        {4},
        {2, 4},
        {},
    };
    vector<vector<double>> C =
    {
        {10.0, 2.0},
        {6.0, 5.9},
        {5.0},
        {3.0, 8.0},
        {},
    };
    cout<<maxflow(E, C, 0, 4)<<endl;
}
