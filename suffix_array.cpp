#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> suffix_array(string s)
{
    int n = (int)s.size();

    vector<int> sa(n);
    vector<int> rank(n);
    vector<int> tmp(n);

    for (int i=0; i<n; i++)
        sa[i] = i;
    sort(sa.begin(), sa.end(), [&](int a, int b){return s[a]<s[b];});
    for (int i=0; i<n; i++)
        rank[i] = s[i];

    for (int k=1; k<n; k*=2)
    {
        auto cmp = [&](int a, int b)
        {
            int ra = a+k<n ? rank[a+k] : -1;
            int rb = b+k<n ? rank[b+k] : -1;
            return rank[a]<rank[b] || rank[a]==rank[b] && ra<rb;
        };

        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i=1; i<n; i++)
            tmp[sa[i]] = tmp[sa[i-1]] + (int)cmp(sa[i-1], sa[i]);
        rank.swap(tmp);
    }

    return sa;
}

#include <iostream>

int main()
{
    vector<int> sa1 = suffix_array("abracadabra");
    //   10 7 0 3 5 8 1 4 6 9 2
    for (int t: sa1)
        cout<<" "<<t;
    cout<<endl;

    vector<int> sa2 = suffix_array("aaaaaaaa");
    //   7 6 5 4 3 2 1 0
    for (int t: sa2)
        cout<<" "<<t;
    cout<<endl;
}
