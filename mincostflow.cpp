#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

long long mincostflow(vector<vector<int>> E, vector<vector<long long>> cap, vector<vector<long long>> cost,
    int s, int t, long long f)
{
    int n = (int)E.size();

    //  reverse edge
    vector<vector<int>> R(n);
    for (int v=0; v<n; v++)
        R[v].resize(E[v].size());
    vector<vector<int>> E_ = E;
    vector<vector<long long>> cap_ = cap;
    vector<vector<long long>> cost_ = cost;

    for (int v=0; v<n; v++)
        for (int e=0; e<(int)E_[v].size(); e++)
        {
            int to = E_[v][e];
            R[v][e] = (int)E[to].size();
            E[to].push_back(v);
            cap[to].push_back(0);
            cost[to].push_back(-cost[v][e]);
            R[to].push_back(e);
        }

    long long oo = 0xfff'ffff'ffff'ffffLL;
    long long res = 0;
    vector<long long> D(n);
    vector<int> prevv(n);
    vector<int> preve(n);
    while (f>0)
    {
        //  Bellman-Ford
        for (long long &d: D)
            d = oo;
        D[s] = 0;
        while (true)
        {
            bool up = false;
            for (int v=0; v<n; v++)
                if (D[v]<oo)
                    for (int e=0; e<(int)E[v].size(); e++)
                    {
                        int to = E[v][e];
                        if (cap[v][e]>0 && D[to]>D[v]+cost[v][e])
                        {
                            D[to] = D[v]+cost[v][e];
                            prevv[to] = v;
                            preve[to] = e;
                            up = true;
                        }
                    }
            if (!up)
                break;
        }

        if (D[t]==oo)
            return oo;

        long long d = f;
        for (int v=t; v!=s; v=prevv[v])
            d = min(d, cap[prevv[v]][preve[v]]);
        f -= d;
        res += d*D[t];
        for (int v=t; v!=s; v=prevv[v])
        {
            cap[prevv[v]][preve[v]] -= d;
            cap[v][R[prevv[v]][preve[v]]] += d;
        }
    }
    return res;
}

#include <iostream>

int main()
{
    vector<vector<int>> E
    {
        {1, 2},
        {2, 3},
        {4},
        {2, 4},
        {},
    };
    vector<vector<long long>> cap
    {
        {10, 2},
        {6, 6},
        {5},
        {3, 8},
        {}
    };
    vector<vector<long long>> cost
    {
        {2, 4},
        {6, 2},
        {2},
        {3, 6},
        {},
    };

    //  80
    cout<<mincostflow(E, cap, cost, 0, 4, 9)<<endl;
}
