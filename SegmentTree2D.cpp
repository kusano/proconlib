#include <vector>
#include <functional>
using namespace std;

template<typename T>
class SegmentTree2D
{
public:
    int w, h;
    function<T(T, T)> op;
    T init;
    vector<vector<T>> V;

    T q(int x1, int y1, int x2, int y2)
    {
        if (x1>=x2 || y1>=y2)
            return init;

        T a = q((x1+1)/2, (y1+1)/2, x2/2, y2/2);
        if (x1%2!=0)
            a = op(a, q(x1, (y1+1)/2, x1+1, y2/2));
        if (x2%2!=0)
            a = op(a, q(x2-1, (y1+1)/2, x2, y2/2));
        if (y1%2!=0)
            a = op(a, q((x1+1)/2, y1, x2/2, y1+1));
        if (y2%2!=0)
            a = op(a, q((x1+1)/2, y2-1, x2/2, y2));
        if (x1%2!=0 && y1%2!=0)
            a = op(a, V[y1][x1]);
        if (x1%2!=0 && y2%2!=0)
            a = op(a, V[y2-1][x1]);
        if (x2%2!=0 && y1%2!=0)
            a = op(a, V[y1][x2-1]);
        if (x2%2!=0 && y2%2!=0)
            a = op(a, V[y2-1][x2-1]);
        return a;
    }

    SegmentTree2D(vector<vector<T>> V_, function<T(T, T)> op, T init)
        : op(op), init(init)
    {
        w = 1;
        while (w<(int)V_[0].size())
            w *= 2;
        h = 1;
        while (h<(int)V_.size())
            h *= 2;
        V = vector<vector<T>>(2*h, vector<T>(2*w, init));
        for (int y=0; y<h; y++)
            for (int x=0; x<w; x++)
                if (x<(int)V_[0].size() && y<(int)V_.size())
                    V[h+y][w+x] = V_[y][x];
        for (int y=h-1; y>0; y--)
            for (int x=w; x<w*2; x++)
                V[y][x] = op(V[y*2][x], V[y*2+1][x]);
        for (int y=0; y<2*h; y++)
            for (int x=w-1; x>0; x--)
                V[y][x] = op(V[y][x*2], V[y][x*2+1]);
    }

    T get(int x, int y) const
    {
        return V[h+y][w+x];
    }

    void set(int x_, int y_, T v)
    {
        V[y_+h][x_+w] = v;

        for (int y=(y_+h)/2; y>0; y/=2)
            V[y][x_+w] = op(V[y*2][x_+w], V[y*2+1][x_+w]);
        for (int y=y_+h; y>0; y/=2)
            for (int x=(x_+w)/2; x>0; x/=2)
                V[y][x] = op(V[y][x*2], V[y][x*2+1]);
    }

    T query(int x1, int y1, int x2, int y2)
    {
        return q(x1+w, y1+h, x2+w, y2+h);
    }
};

#include <iostream>

int main()
{
    SegmentTree2D<int> ST(
        {
            {3, 1, 4, 1, 5},
            {9, 2, 6, 5, 3},
            {5, 8, 9, 7, 9},
        },
        [&](int a, int b){return a+b;}, 0);

    cout<<ST.get(2, 1)<<endl; // 6
    cout<<ST.query(1, 1, 4, 3)<<endl; // 37
    ST.set(3, 2, 0);
    cout<<ST.query(1, 1, 4, 3)<<endl; // 30
}
