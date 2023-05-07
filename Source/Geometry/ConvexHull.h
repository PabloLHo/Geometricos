//
// Created by juli on 12/04/23.
//

#ifndef AG2223_CLION_CONVEXHULL_H
#define AG2223_CLION_CONVEXHULL_H
#include <string>
#include "PointCloud3d.h"
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include "Triangle3d.h"
#include "Vect2d.h"
#include "Line3d.h"
#include "Segment3d.h"

class ConvexHull {
private:
    std::vector<Vect2d> puntos2D;
    std::vector<Vect3d> puntos;
    std::vector<Triangle3d> triangulos;
    std::vector<Segment3d> segments;
public:
    const std::vector<Triangle3d> &getTriangulos() const;
    const std::vector<Segment3d> &getSegments() const;
    const std::vector<Vect2d> &getPuntos2D() const;
    const std::vector<Vect3d>& getPuntos3D() const;

    ConvexHull();
    ConvexHull(std::string path);
    ConvexHull(PointCloud3d nP, int tipo);
};


#endif //AG2223_CLION_CONVEXHULL_H
