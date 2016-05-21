#include <vector>
#include <algorithm>

using namespace std;

template<class T>
T determinant(vector<vector<T>> M)
{
    int n = (int)M.size();
    T d = 1;

    for (int i=0; i<n; i++)
    {
        if (M[i][i]==0)
        {
            int t=-1;
            for (int j=i+1; j<n && t==-1; j++)
                if (M[j][i]!=0)
                    t = j;
            if (t==-1)
                return 0;
            swap(M[i], M[t]);
            d = -d;
        }

        T t = M[i][i];
        for (int j=i; j<n; j++)
            M[i][j] /= t;
        d *= t;

        for (int j=i+1; j<n; j++)
        {
            T t = M[j][i];
            for (int k=i; k<n; k++)
                M[j][k] -= t*M[i][k];
        }
    }

    return d;
}

#include <iostream>

int main()
{
    vector<vector<double>> M = {
        { 0,-2, 0},
        {-1, 3, 1},
        { 4, 2, 1}
    };

    cout<<determinant(M)<<endl; //  -10
}
