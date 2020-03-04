#include <complex>
#include <vector>
using namespace std;

//  |p-o1|=r1, |p-o2|=r2 を満たす2個の点を返す
vector<complex<double>> circle_intersection(complex<double> o1, double r1, complex<double> o2, double r2)
{
    double d = abs(o1-o2);
    double cos = (r1*r1+d*d-r2*r2)/(2*r1*d);
    if (cos<-1.0 || 1.0<cos)
        return vector<complex<double>>();
    complex<double> p(r1*cos, r1*sqrt(1-cos*cos));
    vector<complex<double>> r{p, conj(p)};
    for (complex<double> &t: r)
        t = t*(o2-o1)/abs(o2-o1)+o1;
    return r;
}

#include <iostream>

int main()
{
    //  (2,2)
    //  (3,1)
    for (complex<double> p: circle_intersection(complex<double>(-1.0, -2.0), 5.0, complex<double>(3.0, 2.0), 1.0))
        cout<<p<<endl;
}
