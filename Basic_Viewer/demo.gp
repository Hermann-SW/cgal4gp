read("cgal.Basic_Viewer.4.gp");
points=[[1, 0, 0], [2, -1, 0], [2, 0, -1], [3, 0, 0], [2, 1, 0], [2, 0, 1]];
print("CGAL_convex_hull_3(",points,")");
print(CGAL_convex_hull_3(points));
print();
print("CGAL_draw()");
CGAL_draw()
print();

n=5*13;
s=sqrtint(n);
points=[[x,y,z]|x<-[-s..s];y<-[-s..s];z<-[-s..s],x^2+y^2+z^2==n];
print("#points=",#points);
print("CGAL_convex_hull_3(points)");
print(CGAL_convex_hull_3(points));
print();
print("CGAL_draw()");
CGAL_draw()
print();
print("CGAL_draw_nef()");
CGAL_draw_nef()
