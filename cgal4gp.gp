\\ https://doc.cgal.org/latest/Polytope_distance_d/classCGAL_1_1Width__3.html
\\
install("Width",                           "vG",     "CGAL_Width",                           "./libcgal4gp.so");

install("get_squared_width",               "v&&",    "CGAL_get_squared_width",               "./libcgal4gp.so");
install("get_width_planes",                "v&&",    "CGAL_get_width_planes",                "./libcgal4gp.so");
install("get_width_coefficients",          "v&&&&&", "CGAL_get_width_coefficients",          "./libcgal4gp.so");
install("get_build_direction",             "m",      "CGAL_get_build_direction",             "./libcgal4gp.so");
install("get_all_build_directions",        "v&",     "CGAL_get_all_build_directions",        "./libcgal4gp.so");
install("get_number_of_optimal_solutions", "i",      "CGAL_get_number_of_optimal_solutions", "./libcgal4gp.so");
