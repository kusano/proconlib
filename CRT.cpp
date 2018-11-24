#include <utility>
#include <vector>
using namespace std;

//  (m, (a, b)) s.t. ax+by=gcd(x,y)
template<class T>
pair<T,pair<T,T>> exgcd(T x, T y)
{
    if (y>0)
    {
        pair<T,pair<T,T>> r = exgcd(y, x%y);
        return make_pair(r.first,
            make_pair(r.second.second, r.second.first-x/y*r.second.second));
    }
    else
        return make_pair(x, make_pair(1, 0));
}

//  https://qiita.com/drken/items/ae02240cd1f8edfc86fd
template<class T>
pair<T,T> CRT(vector<T> a, vector<T> m)
{
    T r = 0;
    T M = 1;
    for (int i=0; i<(int)a.size(); i++)
    {
        pair<T,pair<T,T>> x = exgcd(M, m[i]);
        if ((a[i]-r)%x.first != 0)
            return make_pair(0, -1);
        T d = x.first;
        T tmp = (a[i]-r) / d * x.second.first % (m[i]/d);
        r += M * tmp;
        M *= m[i]/d;
    }
    return make_pair((r%M+M)%M, M);
}

#include <iostream>

int main()
{
    //  x%3 == 2
    //  x%5 == 3
    //  x%7 == 2
    pair<int, int> x = CRT(vector<int>{2, 3, 2}, vector<int>{3, 5, 7});
    //  23 105 (x%105 == 23)
    cout<<x.first<<" "<<x.second<<endl;
}
