#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3.h>
#include <CGAL/draw_nef_3.h>
#include <CGAL/draw_polyhedron.h>

#include <pari/pari.h>

#include <vector>

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


typedef CGAL::Exact_predicates_exact_constructions_kernel  __K;
typedef CGAL::Nef_polyhedron_3<__K>                        __Nef_polyhedron;
typedef CGAL::Polyhedron_3<__K>                            __Polyhedron_3;
typedef __K::Point_3                                       __Point_3;


__Polyhedron_3 *__polyh = NULL;
__Nef_polyhedron *__nefph = NULL;

void draw_timeout(GEN ms, bool donef = false) {
    mpz_t zms;
    mpz_init(zms);
    GEN2mpz(zms, ms);
    int ims = mpz_get_si(zms);
    if (ims < 0) { if (donef) CGAL::draw(*__nefph);
                   else       CGAL::draw(*__polyh);
    } else {
        if (donef) { if (!__nefph) {
                         assert(__polyh);
                         __nefph = new __Nef_polyhedron(*__polyh);
                     }
        } else { assert(__polyh);
        }
        pid_t pid = fork();
               if (pid == -1) { exit(1);
        } else if  (pid == 0) { if (donef) CGAL::draw(*__nefph);
                                else       CGAL::draw(*__polyh);
        } else if   (pid > 0) { usleep(1000*ims); kill(pid, SIGKILL);
        }
    }
}

extern "C"
void
draw(GEN ms) {
    draw_timeout(ms);
}

extern "C"
void
draw_nef(GEN ms) {
    draw_timeout(ms, true);
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
    delete __nefph;
    __nefph = NULL;

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

extern "C"
void
make_hexahedron() {
    delete __polyh;
    __polyh = new __Polyhedron_3();
    delete __nefph;
    __nefph = NULL;

    CGAL::make_hexahedron(
        __Point_3(-0.5, -0.5, -0.5),
        __Point_3(0.5,  -0.5, -0.5),
        __Point_3(0.5,   0.5, -0.5),
        __Point_3(-0.5,  0.5, -0.5),
        __Point_3(-0.5,  0.5, 0.5),
        __Point_3(-0.5, -0.5, 0.5),
        __Point_3(0.5,  -0.5, 0.5),
        __Point_3(0.5,   0.5, 0.5),
        *__polyh);
}
