#include <vector>
#include <queue>
#include <functional>
#include <utility>

using namespace std;

//  E[i]: vertexes which can be reased from i
//  W[i]: their weight
template<class T>
vector<T> dijkstra(vector<vector<int>> E, vector<vector<T>> W, int s, T inf)
{
    int n = (int)E.size();

    vector<T> D(n, inf);
    typedef pair<T,int> P;
    priority_queue<P,vector<P>,greater<P>> Q;

    D[s] = T();
    Q.push(make_pair(D[s], s));

    while (!Q.empty())
    {
        T d = Q.top().first;
        int p = Q.top().second;
        Q.pop();
        if (d > D[p])
            continue;
        for (int i=0; i<(int)E[p].size(); i++)
        {
            int t = E[p][i];
            if (d+W[p][i] < D[t])
                D[t] = d+W[p][i],
                Q.push(make_pair(D[t], t));
        }
    }
    return D;
}

#include <iostream>

int main()
{
    /*
    　　　 2　　　10
    　◎───①───④
    　│　　／│　　　│＼5
     5│ 4／　│6 　 3│　⑥
    　│／　　│　　　│／9
    　②───③───⑤
    　　　 2　　　 1
    */

    vector<vector<int>> E = {
        {1, 2},
        {0, 2, 3, 4},
        {0, 1, 3},
        {1, 2, 5},
        {1, 5, 6},
        {3, 4, 6},
        {4, 5},
    };

    vector<vector<int>> W = {
        {2, 5},
        {2, 4, 6, 10},
        {5, 4, 2},
        {6, 2, 1},
        {10, 3, 5},
        {1, 3, 9},
        {5, 9},
    };

    //   0 2 5 7 11 8 16
    vector<int> D = dijkstra(E, W, 0, 9999);
    for (int d: D)
        cout<<" "<<d;
    cout<<endl;
}
