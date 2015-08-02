#include <iostream>
#include <string>

using namespace std;

#include <vector>
template<class T>
ostream &operator<<(ostream &o, const vector<T> &v)
{
    o<<"{";
    bool f = false;
    for (const T &a: v)
        o<<(f?", ":"")<<a,
        f = true;
    o<<"}";
    return o;
}

#include <set>
template<class T>
ostream &operator<<(ostream &o, const set<T> &s)
{
    o<<"{";
    bool f = false;
    for (const T &a: s)
        o<<(f?", ":"")<<a,
        f = true;
    o<<"}";
    return o;
}

#include <utility>
template<class A, class B>
ostream &operator<<(ostream &o, const pair<A, B> &p)
{
    o<<"{"<<p.first<<", "<<p.second<<"}";
    return o;
}

#include <map>
template<class K, class V>
ostream &operator<<(ostream &o, const map<K,V> &m)
{
    o<<"{";
    bool f = false;
    for (const auto &a: m)
        o<<(f?", ":"")<<a,
        f = true;
    o<<"}";
    return o;
}

int main()
{
    vector<int> v = {1, 2, 3};
    cout<<v<<endl;      //  {1, 2, 3}

    set<double> s = {1.1, 2.2, 3.3};
    cout<<s<<endl;      //  {1.1, 2.2, 3.3}

    pair<vector<int>, set<double>> p = {{1, 2}, {0.1}};
    cout<<p<<endl;      //  {{1, 2}, {0.1}}

    map<string, int> m{{"a", 1}, {"b", 2}, {"c", 3}};
    cout<<m<<endl;      //  {{a, 1}, {b, 2}, {c, 3}}
}
