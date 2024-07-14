# cgal4gp
Make CGAL functionality available for PARI/GP.

Needs these libs to be installed:  
- libpari-dev
- libgmp-dev
- libcgal-dev

[JSCAD app link](https://jscad.app/#data:application/gzip;base64,H4sIAMXYkmYAA1XPPWvDMBAG4F2/4rbYIFt206lQKHTp2N14UJWLo2LpVH20ocb/vYpqQiI06F4exHtCwClGF56EmHQ8pY9WkRFv6I20tgk/Qk1yfpwcE4IpsiHCZ1DyAM/g8Stpj9XupSTC0AFnbaddvcEFJiSzhzXjQtrLjNFrDFeiaCavf/FGlSgwdkxWRU0WjNS2ctJLE2pYGICLIeth6Dl0+Y4chgcOzWXc3jlu+pFnu51hf2fvaT+OLFOPMXl7rVQNHe94z/M//5u0R0/mnbSN4ZXsN56rXKSu2cpYXj7N2OLZkS/lltIaVvYH5sr/umEBAAA=) illustrating the demo:  
![res/simple.gp.png](res/simple.gp.png)

Vertical prototype, now with 3 functions from CGAL:
```
$ make
g++  -O3 -ffp-contract=off -fno-strict-aliasing -fPIC -Wall -pedantic -Wextra -Wno-psabi  -c -o cgal4gp.o cgal4gp.cpp
/usr/bin/g++ -o libcgal4gp.so -shared -Wl,-shared  cgal4gp.o -lc -lm -lgmp
gp -q < simple.gp
- Width([[1, 0, 0], [2, -1, 0], [2, 0, -1], [3, 0, 0], [2, 1, 0], [2, 0, 1]])
- get_squared_width(num,denom)
67108864/50331648
4/3
- get_number_of_optimal_solutions()
8
$ 
```

```
$ cat simple.gp 
read("cgal4gp.gp");

points=[[1,0,0],[2,-1,0],[2,0,-1],[3,0,0],[2,1,0],[2,0,1]];
Width(points);
print("- Width(",points,")");
get_squared_width(num,denom);
print("- get_squared_width(num,denom)");
print(num,"/",denom);
num/denom
print("- get_number_of_optimal_solutions()");
get_number_of_optimal_solutions()
$ 
```

https://doc.cgal.org/latest/Polytope_distance_d/classCGAL_1_1Width__3.html  
```
$ cat cgal4gp.gp
\\ https://doc.cgal.org/latest/Polytope_distance_d/classCGAL_1_1Width__3.html
\\
install("Width",                           "vG",  , "./libcgal4gp.so");

install("get_squared_width",               "v&&", , "./libcgal4gp.so");
install("get_number_of_optimal_solutions", "i",   , "./libcgal4gp.so");
$ 
```

Code cleanup done with help of two new Makefile targets:  
```
$ make cpplint
cpplint --filter=-legal/copyright cgal4gp.cpp
Done processing cgal4gp.cpp
$ make cppcheck
cppcheck --enable=all --suppress=missingIncludeSystem cgal4gp.cpp --check-config
Checking cgal4gp.cpp ...
$ 
```
