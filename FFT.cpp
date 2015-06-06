#include <vector>
#include <complex>
#include <cmath>
using namespace std;

vector<complex<double>> FFT(vector<complex<double>> v, bool inv)
{
    double pi = acos(-1.);

    int n = int(v.size());
    int b = 0;
    while (1<<b<n)
        b++;
    
    vector<complex<double>> f(n);
    for (int i=0; i<n; i++)
    {
        int t=0;
        for (int j=0; j<b; j++)
            t = t<<1 | i>>j&1;
        f[t] = v[i];
    }

    vector<complex<double>> w(n);
    for (int i=0; i<n; i++)
    {
        double t = (inv?2:-2)*pi*i/n;
        w[i] = complex<double>(cos(t), sin(t));
    }

    for (int i=0; i<b; i++)
    for (int j=0; j<n; j+=1<<-~i)
    for (int k=0; k<1<<i; k++)
    {
        int l = k+(1<<i);
        complex<double> x = f[j+k];
        complex<double> y = f[j+l];
        f[j+k] = x + y*w[k<<(b-i-1)];
        f[j+l] = x + y*w[l<<(b-i-1)];
    }

    if (inv)
        for (int i=0; i<n; i++)
            f[i] /= n;

    return f;
}

//  ret[i] = ΣA[t]B[i-t]
vector<double> convolution(vector<double> A, vector<double> B)
{
    int n = 1;
    while (n<(int)A.size()+(int)B.size()-1)
        n *= 2;
    vector<complex<double>> a(n), b(n);
    for (int i=0; i<(int)A.size(); i++)
        a[i] = A[i];
    for (int i=0; i<(int)B.size(); i++)
        b[i] = B[i];
    vector<complex<double>> at = FFT(a, false);
    vector<complex<double>> bt = FFT(b, false);
    vector<complex<double>> ct(n);
    for (int i=0; i<n; i++)
        ct[i] = at[i]*bt[i];
    vector<complex<double>> c = FFT(ct, true);
    vector<double> C((int)A.size()+(int)B.size());
    for (int i=0; i<(int)C.size(); i++)
        C[i] = c[i].real();
    return C;
}

//  http://atc001.contest.atcoder.jp/tasks/fft_c
#include <iostream>

int main()
{
    int N;
    cin>>N;
    vector<double> A(N+1), B(N+1);
    for (int i=1; i<=N; i++)
        cin>>A[i]>>B[i];
    vector<double> C = convolution(A, B);
    for (int i=1; i<=2*N; i++)
        cout<<int(C[i]+.5)<<endl;
}
