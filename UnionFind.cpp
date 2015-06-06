#include <vector>
using namespace std;

class UnionFind
{
public:
    vector<int> parent;
    vector<int> rank;
    
    UnionFind(int n): parent(n), rank(n)
    {
        for(int i=0;i<n;i++)
            parent[i] = i,
            rank[i] = 0;
    }

    int root(int x)
    {
        return parent[x]==x ? x : parent[x] = root(parent[x]);
    }

    bool same(int x, int y)
    {
        return root(x)==root(y);
    }

    void unite(int x, int y)
    {
        x = root(x);
        y = root(y);
        if (x != y)
        {
            if (rank[x] < rank[y])
                parent[x] = y;
            else
                parent[y] = x;
            if (rank[x]==rank[y])
                rank[x]++;
        }
    }
};

//  http://atc001.contest.atcoder.jp/tasks/unionfind_a
#include <iostream>

int main()
{
    int N, Q;
    cin>>N>>Q;
    
    UnionFind unionFind(N);

    for (int i=0; i<Q; i++)
    {
        int P, A, B;
        cin>>P>>A>>B;
        if (P==0)
            unionFind.unite(A, B);
        else
            cout<<(unionFind.same(A, B) ? "Yes" : "No")<<endl;
    }
}
