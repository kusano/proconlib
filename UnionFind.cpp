#include <vector>
using namespace std;

class UnionFind
{
public:
    vector<int> parent;
    vector<int> sz;
    
    UnionFind(int n): parent(n), sz(n)
    {
        for(int i=0;i<n;i++)
        {
            parent[i] = i;
            sz[i] = 1;
        }
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
            if (sz[x] < sz[y])
            {
                parent[x] = y;
                sz[y] += sz[x];
            }
            else
            {
                parent[y] = x;
                sz[x] += sz[y];
            }
        }
    }

    int size(int x)
    {
        return sz[root(x)];
    }
};

#include <iostream>

int main()
{
    UnionFind UF(6);

    cout<<UF.same(0, 1)<<endl;  //  0
    
    /*
        0-3  1-2
          |  |/
          5  4
    */
    UF.unite(0, 3);
    UF.unite(3, 5);
    UF.unite(1, 2);
    UF.unite(2, 4);
    UF.unite(4, 1);
    cout<<UF.same(0, 5)<<endl;  //  1
    cout<<UF.same(1, 2)<<endl;  //  1
    cout<<UF.same(0, 1)<<endl;  //  0
    cout<<UF.size(0)<<endl;     //  3
    cout<<UF.size(2)<<endl;     //  3

    UF.unite(3, 4);
    cout<<UF.same(0, 2)<<endl;  //  1
    cout<<UF.size(5)<<endl;     //  6
}
