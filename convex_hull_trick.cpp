#include <set>
#include <iterator>
#include <limits>
#include <functional>
using namespace std;

// https://satanic0258.hatenablog.com/entry/2016/08/16/181331
// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
template<class T>
class ConvexHullTrick
{
    struct Line
    {
        T a, b;
        // X-coordinate of the intersection with the right neighbor.
        T xn, xd;

        bool operator<(const Line &l) const {return a>l.a;}
        bool operator<(T x) const {return xn<x*xd;}
    };

    set<Line, less<>> lines;

    bool need(const Line &l1, const Line &l2, const  Line &l3) const
    {
        return (l3.b-l2.b)*(l1.a-l2.a)>(l2.b-l1.b)*(l2.a-l3.a);
    }

public:
    // Add y = ax+b.
    void add(T a, T b)
    {
        Line l;
        l.a = a;
        l.b = b;

        if (lines.empty())
        {
            l.xd = 1;
            l.xn = numeric_limits<T>::max();
            lines.insert(l);
            return;
        }

        auto it = lines.lower_bound(l);
        if (it!=lines.begin() && a==prev(it)->a)
            it--;
        if (it!=lines.end() && a==it->a)
        {
            if (b>=it->b)
                return;
            it = lines.erase(it);
        }
        else if (it!=lines.begin() && it!=lines.end() && !need(*prev(it), l, *it))
            return;

        if (it!=lines.begin())
        {
            while (true)
            {
                if (prev(it)==lines.begin() ||
                    need(*prev(it, 2), *prev(it), l))
                    break;
                lines.erase(prev(it));
            }

            Line l2 = *prev(it);
            l2.xn = b-l2.b;
            l2.xd = l2.a-a;
            lines.erase(prev(it));
            lines.insert(l2);
        }

        while (true)
        {
            if (it==lines.end() ||
                next(it)==lines.end() ||
                need(l, *it, *next(it)))
                break;
            it = lines.erase(it);
        }
        if (it==lines.end())
        {
            l.xn = numeric_limits<T>::max();
            l.xd = 1;
        }
        else
        {
            l.xn = it->b-b;
            l.xd = a-it->a;
        }
        lines.insert(l);
    }

    // Return min(a_i*x+b_i).
    T min(T x) const
    {
        auto it = lines.lower_bound(x);
        return it->a*x+it->b;
    }
};

#include <iostream>
#include <vector>
#include <cstdlib>

void test()
{
    while (true)
    {
        ConvexHullTrick<int> CHT;
        vector<int> A, B;
        for (int i=0; i<16; i++)
        {
            int a = rand()%17-8;
            int b = rand()%17-8;
            int x = rand()%33-16;
            CHT.add(a, b);
            int ans = CHT.min(x);

            A.push_back(a);
            B.push_back(b);
            int naive = 99999999;
            for (int j=0; j<(int)A.size(); j++)
                naive = min(naive, A[j]*x+B[j]);

            if (ans!=naive)
            {
                cout<<"NG"<<endl;
                for (int j=0; j<(int)A.size(); j++)
                    cout<<A[j]<<" "<<B[j]<<endl;
                cout<<x<<endl;
                cout<<ans<<endl;
                cout<<naive<<endl;
                return;
            }
        }
        cout<<"OK"<<endl;
    }
}

int main()
{
    // test();

    ConvexHullTrick<int> CHT;
    CHT.add(1, 1);
    cout<<CHT.min(0)<<endl; // 1
    cout<<CHT.min(1)<<endl; // 2
    cout<<CHT.min(2)<<endl; // 3
    CHT.add(-1, 3);
    cout<<CHT.min(1)<<endl; // 2
    cout<<CHT.min(2)<<endl; // 1
    CHT.add(0, 3);
    cout<<CHT.min(1)<<endl; // 2
    CHT.add(0, 1);
    cout<<CHT.min(1)<<endl; // 1
}
