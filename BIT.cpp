#include <vector>
using namespace std;

//  Binary Indexed Tree
/*
|       8       |   |
|   4   |       |   |
| 2 |   | 6 |   |10 |
|1| |3| |5| |7| |9| |
*/
template<class T>
class BIT
{
    int n;
    vector<T> v;
public:
    BIT(int n): n(n+1) {
        v = vector<T>(n+1);
    }
    //  a[i] += x
    void add(int p, T x) {
        p++;
        for (; p<n; p+=p&-p)
            v[p] += x;
    }
    //  return a[0]+a[1]+…+a[i-1]
    T sum(int p) {
        T s = T();
        for (; p>0; p-=p&-p)
            s += v[p];
        return s;
    }

    //  return min[x](sum(x+1)>=k)
    int nth(T k) {
        k++;
        int r = 0;
        int b = 1;
        while (b<n)
            b <<= 1;
        for (; b>0; b>>=1)
            if (r+b<n && v[r+b]<k)
            {
                r += b;
                k -= v[r];
            }
        return r;
    }
};

#include <iostream>

int main()
{
    BIT<int> bit(8);

    cout<<bit.sum(0)<<endl; //  0
    cout<<bit.sum(8)<<endl; //  0

    bit.add(0, 1);
    bit.add(6, 5);

    cout<<bit.sum(0)<<endl; //  0
    cout<<bit.sum(1)<<endl; //  1
    cout<<bit.sum(7)<<endl; //  6

    bit.add(6, -5);

    cout<<bit.sum(7)<<endl; //  1

    bit.add(3, 2);
    bit.add(5, 1);
    cout<<bit.nth(1)<<endl; //  3
    cout<<bit.nth(2)<<endl; //  3
    cout<<bit.nth(3)<<endl; //  5
    cout<<bit.nth(4)<<endl; //  8 (sum(8)<4)
}
