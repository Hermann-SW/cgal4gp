cmake_minimum_required(VERSION 3.1...3.23)

project(Basic_Viewer)

add_compile_options(-O3 -ffp-contract=off -fno-strict-aliasing -fPIC -std=c++14)

add_link_options(-shared -Wl,-shared)    # this makes "executable" a shared lib

find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)

find_package(CGAL REQUIRED)

create_single_source_cgal_program("Qt.cpp")

if(CGAL_Qt5_FOUND)
  target_link_libraries(Qt PUBLIC CGAL::CGAL_Basic_viewer)
endif()
