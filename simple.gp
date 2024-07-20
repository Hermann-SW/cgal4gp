read("cgal4.gp");

points=[[1,0,0],[2,-1,0],[2,0,-1],[3,0,0],[2,1,0],[2,0,1]];

print("- Width(",points,")");
CGAL_Width(points);

print("- get_squared_width(num,denom)");
CGAL_get_squared_width(num,denom);
print(num,"/",denom);
num/denom

print("- get_width_planes(e1,e2)");
CGAL_get_width_planes(e1,e2);
print(e1," ",e2);

print("- get_width_coefficients(A,B,C,D,K)");
CGAL_get_width_coefficients(A,B,C,D,K);
print(A," ",B," ",C," ",D," ",K);
print("width-plane e1(e2) is given by the equation Ax+By+Cz+D(K)=0"); 

print("- get_build_direction()");
CGAL_get_build_direction()

print("- get_all_build_directions(dir)");
CGAL_get_all_build_directions(dir);
dir

print("- get_number_of_optimal_solutions()");
CGAL_get_number_of_optimal_solutions()

print("workaround(all build directions): ", Set([d/gcd(d)*if(d[1]<0,-1,1) | d<-dir]));
