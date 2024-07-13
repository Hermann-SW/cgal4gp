#include <pari/pari.h>


#include <CGAL/Homogeneous.h>
#include <CGAL/Width_default_traits_3.h>
#include <CGAL/Width_3.h>
#include <iostream>
#include <vector>

typedef CGAL::Gmpz                            RT;

typedef CGAL::Homogeneous<RT>                 Kernel;
typedef Kernel::Point_3                       Point_3;
typedef Kernel::Plane_3                       Plane_3;
typedef CGAL::Width_default_traits_3<Kernel>  Width_traits;
typedef CGAL::Width_3<Width_traits>           Width;


// from 2007 posting: https://pari.math.u-bordeaux.fr/archives/pari-users-0712/msg00001.html
#define LIMBS(x)  (reinterpret_cast<mp_limb_t *>((x)+2))
#define NLIMBS(x) (lgefint(x)-2)
void
GEN2mpz(mpz_t X, GEN x) {
    int64_t l = NLIMBS(x);
    X->_mp_alloc = l;
    X->_mp_size = signe(x) > 0? l: -l;
    X->_mp_d = LIMBS(x); /* shallow! */
}
GEN
mpz2GEN(mpz_t X) {
    int64_t l = X->_mp_size, lx = labs(l)+2;
    GEN x = cgeti(lx);
    x[1] = evalsigne(l > 0? 1: -1) | evallgefint(lx);
    for (int i = 2; i < lx; i++) x[i] = X->_mp_d[i-2];
    return x;
}


extern "C"
void
get_squared_width(GEN points, GEN *num, GEN *denom)
{
    std::vector<Point_3> pts;
    mpz_t x, y, z;
    mpz_init(x);
    mpz_init(y);
    mpz_init(z);
    for(int i=1; i<lg(points); ++i) {
        GEN2mpz(x, gel(gel(points,i),1));
        GEN2mpz(y, gel(gel(points,i),2));
        GEN2mpz(z, gel(gel(points,i),3));
        pts.push_back(Point_3(x, y, z));
    }

    // Compute width of simplex
    Width simplex(pts.begin(), pts.end());

    RT wnum, wdenom;
    simplex.get_squared_width(wnum, wdenom);

    *num = mpz2GEN(wnum.mpz());
    *denom = mpz2GEN(wdenom.mpz());
}
