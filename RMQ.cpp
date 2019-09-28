#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

//  RMQ
template<class T>
class RMQ
{
    int n;
    vector<T> A;

    T q(int l, int r)
    {
        T a = min(A[l], A[r-1]);
        if ((l+1)/2 < r/2)
            a = min(a, q((l+1)/2, r/2));
        return a;
    }

public:
    RMQ(int n_)
    {
        n = 1;
        while (n < n_)
            n *= 2;
        A = vector<T>(2*n, numeric_limits<T>::max());
    }

    void set(int i, T v)
    {
        A[i+n] = v;
        for (int p=(i+n)/2; p>0; p/=2)
            A[p] = min(A[2*p], A[2*p+1]);
    }

    //  [l, r)
    //  if l>=r return invalid
    T query(int l, int r, T invalid)
    {
        if (l<r)
            return q(l+n, r+n);
        else
            return invalid;
    }
};

#include <iostream>

int main()
{
    vector<int> v = {5, 7, -2, 3, -4};
    int n = (int)v.size();

    RMQ<int> Q(n);
    for (int i=0; i<n; i++)
        Q.set(i, v[i]);

    cout<<Q.query(0, 1, 99)<<endl;  //  5
    cout<<Q.query(1, 4, 99)<<endl;  //  -2
    cout<<Q.query(1, 5, 99)<<endl;  //  -4
    Q.set(4, 0);
    cout<<Q.query(1, 5, 99)<<endl;  //  -2
    cout<<Q.query(2, 2, 99)<<endl;  //  99
}
