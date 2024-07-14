#include <pari/pari.h>

#include <CGAL/Homogeneous.h>
#include <CGAL/Width_default_traits_3.h>
#include <CGAL/Width_3.h>
#include <cassert>
#include <vector>

typedef CGAL::Gmpz                            _RT;

typedef CGAL::Homogeneous<_RT>                _Kernel;
typedef _Kernel::Point_3                      _Point_3;
typedef _Kernel::Vector_3                     _Vector_3;
typedef _Kernel::Plane_3                      _Plane_3;
typedef CGAL::Width_default_traits_3<_Kernel> _Width_traits;
typedef CGAL::Width_3<_Width_traits>          _Width;


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


_Width *_simplex = NULL;

extern "C"
void
Width(GEN points) {
    std::vector<_Point_3> pts;
    mpz_t x, y, z;
    mpz_init(x);
    mpz_init(y);
    mpz_init(z);
    for (int i = 1; i < lg(points); ++i) {
        GEN2mpz(x, gel(gel(points, i), 1));
        GEN2mpz(y, gel(gel(points, i), 2));
        GEN2mpz(z, gel(gel(points, i), 3));
        pts.push_back(_Point_3(x, y, z));
    }

    delete _simplex;
    _simplex = new _Width(pts.begin(), pts.end());
}

extern "C"
void
get_squared_width(GEN *num, GEN *denom) {
    _RT wnum, wdenom;

    assert(_simplex != NULL);
    _simplex->get_squared_width(wnum, wdenom);

    *num = mpz2GEN(wnum.mpz());
    *denom = mpz2GEN(wdenom.mpz());
}

extern "C"
GEN
get_build_direction() {
    assert(_simplex != NULL);
    _Vector_3 _dir = _simplex->get_build_direction();

    return mkvec3(
               mkfrac(
                   mpz2GEN(_dir[0].num.mpz()),
                   mpz2GEN(_dir[0].den.mpz())),
               mkfrac(
                   mpz2GEN(_dir[1].num.mpz()),
                   mpz2GEN(_dir[1].den.mpz())),
               mkfrac(
                   mpz2GEN(_dir[2].num.mpz()),
                   mpz2GEN(_dir[2].den.mpz())));
}

extern "C"
void
get_all_build_directions(GEN *dir) {
    std::vector<_Vector_3> _dir;

    assert(_simplex != NULL);
    _simplex->get_all_build_directions(_dir);

    GEN ret = cgetg(1, t_VEC);

    for (std::vector<_Vector_3>::iterator it = _dir.begin();
         it != _dir.end(); it++
    ) {
        ret = vec_append(
                  ret,
                  mkvec3(
                      mkfrac(
                          mpz2GEN(((*it)[0]).num.mpz()),
                          mpz2GEN(((*it)[0]).den.mpz())),
                      mkfrac(
                          mpz2GEN(((*it)[1]).num.mpz()),
                          mpz2GEN(((*it)[1]).den.mpz())),
                      mkfrac(
                          mpz2GEN(((*it)[2]).num.mpz()),
                          mpz2GEN(((*it)[2]).den.mpz()))));
    }

    *dir = ret;
}

extern "C"
int
get_number_of_optimal_solutions() {
    assert(_simplex != NULL);
    return _simplex->get_number_of_optimal_solutions();
}

