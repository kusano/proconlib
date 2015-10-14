#include <vector>
using namespace std;

//  Binary Indexed Tree
class BIT
{
    int n;
    vector<int> v;
public:
    BIT(int n_) {
        n = 1;
        while (n < n_)
            n <<= 1;
        v = vector<int>(n);
    }
    //  a[i] += x
    void add(int i, int x) {
        for (; i<n; i|=i+1)
            v[i] += x;
    }
    //  return a[0]+a[1]+c+a[i-1]
    int sum(int i) {
        int s = 0;
        for (i--; i>=0; i=(i&(i+1))-1)
            s += v[i];
        return s;
    }
};

#include <iostream>

int main()
{
    BIT bit(8);

    cout<<bit.sum(0)<<endl; //  0
    cout<<bit.sum(8)<<endl; //  0

    bit.add(0, 1);
    bit.add(6, 5);

    cout<<bit.sum(0)<<endl; //  0
    cout<<bit.sum(1)<<endl; //  1
    cout<<bit.sum(7)<<endl; //  6

    bit.add(6, -5);

    cout<<bit.sum(7)<<endl; //  1
}
