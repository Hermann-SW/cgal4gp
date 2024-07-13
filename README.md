# cgal4gp
Make CGAL functionality available for PARI/GP

Initial commit with identity only, C++ but without cgal yet:  
```
$ make
g++  -I. -I/usr/local/include -fPIC  -c -o cgal4gp.o cgal4gp.cpp
/usr/bin/gcc -o libcgal4gp.so -shared  -O3 -Wall -ffp-contract=off -fno-strict-aliasing -fPIC -Wl,-shared   cgal4gp.o -lc -lm -L/usr/local/lib 
gp -q < simple.gp
[[1, 0, 0], [2, -1, 0], [2, 0, -1], [3, 0, 0], [2, 1, 0], [2, 0, 1]]
$ 
$ cat simple.gp 
install("squared_width_3", "G", "f", "./libcgal4gp.so");
f([[1,0,0],[2,-1,0],[2,0,-1],[3,0,0],[2,1,0],[2,0,1]])
$ 
$ tail -6 cgal4gp.cpp 
extern "C"
GEN
squared_width_3(GEN points)
{
  return points;
}
$ 
```
