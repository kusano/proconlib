#include <vector>
#include <functional>
using namespace std;

/*
R[p] = ident;
for (int e: E[p])
    R[p] = g(R[p], f(R[e]));
*/
template<class T>
vector<T> rerooting(
    vector<vector<int>> E,
    T ident,
    function<T(T)> f,
    function<T(T, T)> g)
{
    int n = (int)E.size();
    vector<T> R(n, ident);
    vector<T> X(n, ident); // without parent.

    function<void(int, int)> dfs1 = [&](int c, int p)
        {
            for (int e: E[c])
                if (e!=p)
                {
                    dfs1(e, c);
                    X[c] = g(X[c], f(X[e]));
                }
        };
    dfs1(0, -1);

    function<void(int, int, T)> dfs2 = [&](int c, int p, T x)
        {
            R[c] = g(x, X[c]);

            int en = (int)E[c].size();

            vector<T> TL(en, ident);
            T t = x;
            for (int i=0; i<en; i++)
                if (E[c][i]!=p)
                {
                    TL[i] = t;
                    t = g(t, f(X[E[c][i]]));
                }
            vector<T> TR(en, ident);
            t = ident;
            for (int i=en-1; i>=0; i--)
                if (E[c][i]!=p)
                {
                    TR[i] = t;
                    t = g(t, f(X[E[c][i]]));
                }

            for (int i=0; i<en; i++)
                if (E[c][i]!=p)
                    dfs2(E[c][i], c, f(g(TL[i], TR[i])));
        };
    dfs2(0, -1, ident);

    return R;
}

#include <iostream>
#include <algorithm>

int main()
{
    /*
    0 - 1 - 2
        |
        3 - 4 - 5
    */
    vector<vector<int>> E = {
        {1},
        {0, 2, 3},
        {1},
        {1, 4},
        {3, 5},
        {4},
    };

    vector<int> D = rerooting<int>(
        E,
        0,
        [](int d) {return d+1;},
        [](int x, int y) {return max(x, y);});
    // 4 3 4 2 3 4
    for (int d: D)
        cout<<" "<<d;
    cout<<endl;

    return 0;
}
