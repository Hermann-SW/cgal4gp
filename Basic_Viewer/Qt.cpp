#include <pari/pari.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3.h>
#include <CGAL/draw_polyhedron.h>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel  __K;
typedef CGAL::Polyhedron_3<__K>                              __Polyhedron_3;
typedef __K::Point_3                                         __Point_3;

__Polyhedron_3 *__polyh = NULL;

extern "C"
void
draw()
{
  assert(__polyh);
  CGAL::draw(*__polyh);
}

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
    x[1] = evalsigne(l > 0? 1: (l < 0 ? - 1 : 0)) | evallgefint(lx);
    for (int i = 2; i < lx; i++) x[i] = X->_mp_d[i-2];
    return x;
}


extern "C"
GEN
convex_hull_3(GEN points) {
    std::vector<__Point_3> pts;
    mpz_t x, y, z;
    mpz_init(x);
    mpz_init(y);
    mpz_init(z);
    for (int i = 1; i < lg(points); ++i) {
        GEN2mpz(x, gel(gel(points, i), 1));
        GEN2mpz(y, gel(gel(points, i), 2));
        GEN2mpz(z, gel(gel(points, i), 3));
        pts.push_back(__Point_3(mpz_get_si(x), mpz_get_si(y), mpz_get_si(z)));
    }

  delete __polyh;
  __polyh = new __Polyhedron_3();
  CGAL::convex_hull_3(pts.begin(), pts.end(), *__polyh);

  GEN ret = cgetg(1, t_VEC);
  mpz_t a;
  mpz_init(a);
  mpz_set_ui(a, num_vertices(*__polyh));
  ret = vec_append(ret, mpz2GEN(a));
  mpz_set_ui(a, num_edges(*__polyh));
  ret = vec_append(ret, mpz2GEN(a));
  mpz_set_ui(a, num_halfedges(*__polyh));
  ret = vec_append(ret, mpz2GEN(a));
  mpz_set_ui(a, num_faces(*__polyh));
  ret = vec_append(ret, mpz2GEN(a));

  return ret;
}
