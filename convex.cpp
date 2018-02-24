#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

template<class T>
vector<int> convex(vector<T> x, vector<T> y)
{
    int n = (int)x.size();
    vector<pair<pair<T,T>, int>> Pt(n);
    for (int i=0; i<n; i++)
        Pt[i] = make_pair(make_pair(x[i], y[i]), i);
    sort(Pt.begin(), Pt.end());
    vector<int> P(n);
    for (int i=0; i<n; i++)
        P[i] = Pt[i].second;

    vector<int> ans;

    auto f = [&](int i)
    {
        while ((int)ans.size()>=2)
        {
            int t = (int)ans.size();
            T p = (x[P[i]]-x[ans[t-1]])*(y[ans[t-1]]-y[ans[t-2]])
                - (x[ans[t-1]]-x[ans[t-2]])*(y[P[i]]-y[ans[t-1]]);
            if (p < 0)
                ans.pop_back();
            else
                break;
        }
        ans.push_back(P[i]);
    };

    ans.push_back(P[0]);
    ans.push_back(P[1]);
    for (int i=2; i<n; i++)
        f(i);
    ans.push_back(P[n-2]);
    for (int i=n-3; i>=0; i--)
        f(i);
    ans.pop_back();
    return ans;
}

#include <iostream>

int main()
{
    vector<int> c = convex(
        vector<int>{ 0,  8,  5,  6, 10},
        vector<int>{ 0,  2,  4,  2,  3});
    /*
        y     2
        ^          4
        |      3 1
        |
        |0
        +------------->x
    */

    //  0 2 4 1
    for (int t: c)
        cout<<" "<<t;
    cout<<endl;
}
