#include <vector>
#include <functional>

using namespace std;

template<typename T>
class SegmentTree
{
    int n;
    function<T(T,T)> op;
    vector<T> V;

    T q(int l, int r)
    {
        if (l >= r)
            return V[0];
        T a = q((l+1)/2, r/2);
        if (l%2 != 0)
            a = op(a, V[l]);
        if (r%2 != 0)
            a = op(a, V[r-1]);
        return a;
    }

public:
    SegmentTree(int n_, function<T(T,T)> op, T init):
        op(op)
    {
        n = 1;
        while (n < n_)
            n *= 2;
        V = vector<T>(2*n, init);
        for (int i=n-1; i>0; i--)
            V[i] = op(V[i*2], V[i*2+1]);
    }

    T get(int p) const
    {
        return V[p+n];
    }

    void set(int p, T v)
    {
        p += n;
        V[p] = v;
        for (p/=2; p>0; p/=2)
            V[p] = op(V[p*2], V[p*2+1]);
    }

    //  init OP v[l] OP v[l+1] OP ... OP v[r-1]
    T query(int l, int r)
    {
        return q(l+n, r+n);
    }
};

#include <iostream>

int main()
{
    SegmentTree<int> tree(5, [](int a, int b){return a*b;}, 1);

    tree.set(0, 3);
    tree.set(1, 1);
    tree.set(2, 5);
    tree.set(3, 2);
    tree.set(4, 4);

    cout<<tree.get(2)<<endl;        //  5
    cout<<tree.query(0, 2)<<endl;   //  3
    cout<<tree.query(1, 4)<<endl;   //  10

    tree.set(2, 0);

    cout<<tree.query(1, 4)<<endl;   //  0
}
