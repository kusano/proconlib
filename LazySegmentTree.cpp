#include <vector>
#include <functional>
using namespace std;

/*
|       1       |
|   2   |   3   |
| 4 | 5 | 6 | 7 |
|8|9|a|b|c|d|e|f|
*/
template<class S, class F>
class LazySegmentTree
{
    int n;
    int nl;
    function<S(S, S)> op;
    S e;
    function<S(F, S)> mapping;
    function<F(F, F)> composition;
    F id;

    vector<S> data;
    vector<F> lazy;
public:
    LazySegmentTree(int n_, function<S(S, S)> op, S e, function<S(F, S)> mapping, function<F(F, F)> composition, F id):
        op(op), e(e), mapping(mapping), composition(composition), id(id) {
        n = 1;
        nl = 0;
        while (n<n_)
        {
            n *= 2;
            nl++;
        }
        data = vector<S>(n*2, e);
        lazy = vector<F>(n*2, id);
    }
    void set(int p, S v) {
        p += n;
        for (int i=nl+1; i>=0; i--)
            eval(p>>i);
        data[p] = v;
        while (p>1) {
            p /= 2;
            eval(2*p);
            eval(2*p+1);
            data[p] = op(data[2*p], data[2*p+1]);
        }
    }
    S get(int p) {
        p += n;
        for (int i=nl+1; i>=0; i--)
            eval(p>>i);
        return data[p];
    }
    //  [l, r)
    S prod(int l, int r) {
        return prod(l, r, 1, 0, n);
    }
    void apply(int l, int r, F f) {
        return apply(l, r, 1, 0, n, f);
    }
private:
    S prod(int l, int r, int x, int xl, int xr) {
        if (xr<=l || r<=xl)
            return e;
        eval(x);
        if (l<=xl && xr<=r)
            return data[x];
        return op(
            prod(l, r, 2*x, xl, (xl+xr)/2),
            prod(l, r, 2*x+1, (xl+xr)/2, xr));
    }
    void apply(int l, int r, int x, int xl, int xr, F f) {
        eval(x);
        if (xr<=l || r<=xl)
            return;
        if (l<=xl && xr<=r) {
            lazy[x] = composition(f, lazy[x]);
            eval(x);
        } else {
            apply(l, r, 2*x, xl, (xl+xr)/2, f);
            apply(l, r, 2*x+1, (xl+xr)/2, xr, f);
            data[x] = op(data[2*x], data[2*x+1]);
        }
    }
    void eval(int x) {
        if (lazy[x]==id)
            return;
        if (x<n) {
            lazy[2*x] = composition(lazy[x], lazy[2*x]);
            lazy[2*x+1] = composition(lazy[x], lazy[2*x+1]);
        }
        data[x] = mapping(lazy[x], data[x]);
        lazy[x] = id;
    }
};

#include <iostream>

int main()
{
    //  range add, range min
    LazySegmentTree<int, int> LST(
        6,
        [](int a, int b) {return min(a, b);},
        9999,
        [](int f, int s) {return s+f;},
        [](int f, int g) {return f+g;},
        0);

    LST.set(0, 3);
    LST.set(1, 1);
    LST.set(2, 4);
    LST.set(3, 1);
    LST.set(4, 5);
    LST.set(5, 9);
    //  3 1 4 1 5 9
    cout<<LST.prod(0, 3)<<endl; // 1
    cout<<LST.prod(4, 6)<<endl; // 5
    LST.apply(1, 4, 1);
    //  3 2 5 2 5 9
    cout<<LST.prod(0, 6)<<endl; // 2
    LST.apply(2, 5, 2);
    //  3 2 7 4 7 9
    LST.apply(4, 5, -1);
    //  3 2 7 4 6 9
    cout<<LST.get(4)<<endl; // 6
    LST.set(4, 1);
    //  3 2 7 4 1 9
    cout<<LST.get(4)<<endl; // 1
    cout<<LST.prod(0, 6)<<endl; // 1
}
