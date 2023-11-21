#include <iostream>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <vector>
#include <algorithm>
using namespace std;
using namespace std::chrono;

const double TIME = 1.8;

const int expN = 1024;
const double expX = 16;
int expT[expN];

void my_exp_init()
{
    for (int x=0; x<expN; x++)
    {
        double x2 = (double)-x/expN*expX;
        double e = exp(x2)*0x80000000+.5;
        if (e>=0x7fffffff)
            expT[x] = 0x7fffffff;
        else
            expT[x] = int(e);
    }
}

//  exp(t)*0x80000000;
int my_exp(double x)
{
    int x2 = int(x/-expX*expN+.5);
    if (x2<0)
        return expT[0];
    if (x2>=expN)
        return expT[expN-1];
    return expT[x2];
}

int xor64() {
    static uint64_t x = 88172645463345263ULL;
    x ^= x<<13;
    x ^= x>> 7;
    x ^= x<<17;
    return int(x&0x7fffffff);
}

int main()
{
    int N = 1024;
    vector<double> X(N), Y(N);
    for (int i=0; i<N; i++)
    {
        X[i] = xor64()/2147483648.;
        Y[i] = xor64()/2147483648.;
    }

    system_clock::time_point start = system_clock::now();

    my_exp_init();

    vector<int> P(N+1);
    for (int i=0; i<N; i++)
        P[i] = i;
    P[N] = 0;

    double score = 0;
    for (int i=0; i<N; i++)
        score -= hypot(X[P[i]]-X[P[i+1]], Y[P[i]]-Y[P[i+1]]);

    double best_score = score;
    vector<int> best_P = P;

    double temp_inv;
    int iter;
    for (iter=0; ; iter++)
    {
        if (iter%0x1000==0)
        {
            system_clock::time_point now = system_clock::now();
            double time = chrono::duration_cast<chrono::nanoseconds>(now-start).count()*1e-9/TIME;
            if (time>1.0)
                break;
            double temp = 0.5*(1.0-time);
            temp_inv = 1./temp;
        }

        int p1, p2;
        do
        {
            p1 = rand()%N;
            p2 = rand()%N;
        }
        while (p1>=p2);

        double score2 = score
            + hypot(X[P[p1  ]]-X[P[p1+1]], Y[P[p1  ]]-Y[P[p1+1]])
            + hypot(X[P[p2  ]]-X[P[p2+1]], Y[P[p2  ]]-Y[P[p2+1]])
            - hypot(X[P[p1  ]]-X[P[p2  ]], Y[P[p1  ]]-Y[P[p2  ]])
            - hypot(X[P[p1+1]]-X[P[p2+1]], Y[P[p1+1]]-Y[P[p2+1]]);

        if (score2>score ||
            //exp((score2-score)*temp_inv)*0x80000000>xor64())
            my_exp((score2-score)*temp_inv)>xor64())
        {
            score = score2;
            reverse(P.begin()+p1+1, P.begin()+p2+1);

            if (score>best_score)
            {
                best_score = score;
                best_P = P;
            }
        }
    }

    cerr<<"Iteration: "<<iter<<endl;
    cerr<<"Score: "<<best_score<<endl;

    for (int i=0; i<N+1; i++)
        cout<<X[best_P[i]]<<" "<<Y[best_P[i]]<<endl;
}
