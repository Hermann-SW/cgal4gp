cmake_minimum_required(VERSION 3.1...3.23)

project(Basic_Viewer)

add_compile_options(-O3 -ffp-contract=off -fno-strict-aliasing -fPIC -std=c++14)

find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)

find_package(CGAL REQUIRED)

add_library(cgal.Basic_Viewer.4gp SHARED "cgal.Basic_Viewer.4gp.cpp")

if(CGAL_Qt5_FOUND)
  target_link_libraries(cgal.Basic_Viewer.4gp PUBLIC CGAL::CGAL_Basic_viewer)
endif()
