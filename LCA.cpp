#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

//  last common ancestor
class LCA
{
    int n;
    vector<vector<int>> P;
    vector<int> D;

public:
    //  a in E[b] <=> b in E[a]
    LCA(vector<vector<int>> E, int root)
    {
        n = (int)E.size();
        P = vector<vector<int>>(n);
        D = vector<int>(n);

        function<void (int, int, int)> f = [&](int c, int p, int d)
        {
            D[c] = d;

            if (d>0)
                P[c].push_back(p);
            for (int i=1; 1<<i<=d; i++)
                P[c].push_back(P[P[c][i-1]][i-1]);

            for (int e: E[c])
                if (e != p)
                    f(e, c, d+1);
        };
        f(root, -1, 0);
    }

    int query(int a, int b)
    {
        if (D[a]>D[b])
            swap(a, b);

        int d = D[b]-D[a];
        for (int i=0; d>0; i++)
        {
            if (d&1)
                b = P[b][i];
            d >>= 1;
        }

        if (a==b)
            return a;

        int i = 0;
        while (1<<(i+1)<=D[a])
            i++;
        for (; i>=0; i--)
            if (1<<i<=D[a] && P[a][i]!=P[b][i])
            {
                a = P[a][i];
                b = P[b][i];
            }

        if (D[a]>0)
            a = P[a][0];
        return a;
    }
};

#include <iostream>

int main()
{
/*
          2
       +--+--+
       0     9
   +---+---+
   1   3   7
     +-+-+ |
     4   6 8
     |
     5
*/
    LCA lca({
        {1, 2, 3, 7},   //  0
        {0},            //  1
        {0, 9},         //  2
        {0, 4, 6},      //  3
        {3, 5},         //  4
        {4},            //  5
        {3},            //  6
        {0, 8},         //  7
        {7},            //  8
        {2},            //  9
        }, 2);

    cout<<lca.query(5, 6)<<endl;    //  3
    cout<<lca.query(4, 8)<<endl;    //  0
    cout<<lca.query(5, 9)<<endl;    //  2
    cout<<lca.query(0, 8)<<endl;    //  0
}
