#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//  Manacher's algorithm
//  2|w|-1の長さの配列を返す
//  i番目の要素は、i/2を中心とする極大回文の長さの2倍
vector<int> maximalPalindrome(string w)
{
    size_t n = (int)w.size();
    vector<int> P(2*n-1, -1);
    int r = -1;
    int i;
    for (int c=0; c<2*n-1;)
    {
        if (r == -1)
        {
            r = (c+1)%2;
            i = c/2+1;
        }
        int j = c - i;
        while (0<=j && i<n && w[j]==w[i])
        {
            i++;
            j--;
            r += 2;
        }
        P[c] = r;
        int d, rl;
        bool f = false;
        for (d=1; d<=r && 0<c-d && c+d<2*n-1; d++)
        {
            rl = P[c-d];
            if (rl == r-d)
            {
                f = true;
                break;
            }
            int rr = min(r-d, rl);
            P[c+d] = rr;
        }
        r = f ? rl : -1;
        c += d;
    }
    return P;
}

int main()
{
    vector<int> P1 = maximalPalindrome("a");
    for (int p: P1)
        cout<<" "<<p;
    cout<<endl;
    //  a
    //  1

    vector<int> P2 = maximalPalindrome("aaaaba");
    for (int p: P2)
        cout<<" "<<p;
    cout<<endl;
    //  a   a   a   a   b   a
    //  1 2 3 4 3 2 1 0 3 0 1
}
