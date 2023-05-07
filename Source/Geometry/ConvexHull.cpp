//
// Created by juli on 12/04/23.
//
#include "stdafx.h"
#include "ConvexHull.h"
#include "TriangleModel.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include "CGAL/Polyhedron_3.h"
#include "Segment3d.h"
#include <CGAL/Surface_mesh.h>
#include <CGAL/convex_hull_3.h>

#include <CGAL/point_generators_3.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include <CGAL/IO/Polyhedron_iostream.h>

class Polyhedron;

ConvexHull::ConvexHull() {

}

ConvexHull::ConvexHull(std::string path) {

    typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
    typedef CGAL::Polyhedron_3<K>                     Polyhedron_3;
    typedef K::Point_3                                Point_3;
    typedef CGAL::Surface_mesh<Point_3>               Surface_mesh;

    std::vector<Point_3> points;
    Point_3 p;
    TriangleModel *modelo = new TriangleModel(path);
    // compute convex hull of non-collinear points
    for (int i = 0; i < modelo->getVertices()->size(); i++) {
        p = Point_3(modelo->getVertices()->at(i).getX(), modelo->getVertices()->at(i).getY(), modelo->getVertices()->at(i).getZ());
        points.push_back(p);
    }

    Surface_mesh sm;
    CGAL::convex_hull_3(points.begin(), points.end(), sm);

    //iterate each edge of the convex hull
    for (auto e : edges(sm)) {
        //get the two vertices of the edge
        auto v1 = sm.vertex(e, 0);
        auto v2 = sm.vertex(e, 1);
        //get the points
        Point_3 p1 = sm.point(v1);
        Point_3 p2 = sm.point(v2);

        Vect3d vec1(p1.x(), p1.y(), p1.z());
        Vect3d vec2(p2.x(), p2.y(), p2.z());
        //create a segment
        Segment3d s(vec1, vec2);
        //add the segment to the list of segments
        segments.push_back(s);
        puntos.push_back(vec1);
    }


    //create triangles from the points
    for (int i = 0; i < puntos.size(); i++) {
        Vect3d vec1 = puntos[i];
        Vect3d vec2 = puntos[(i + 1) % puntos.size()];
        Vect3d vec3 = puntos[(i + 2) % puntos.size()];
        Triangle3d t(vec1, vec2, vec3);
        triangulos.push_back(t);
    }

    //delete modelo;
}

ConvexHull::ConvexHull(PointCloud3d nP, int tipo) {
    if (tipo) {
        typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
        typedef CGAL::Polyhedron_3<K>                     Polyhedron_3;
        typedef K::Point_3                                Point_3;
        typedef CGAL::Surface_mesh<Point_3>               Surface_mesh;

        std::vector<Point_3> points;
        Point_3 p;
        for (int i = 0; i < nP.size(); i++) {
            p = Point_3(nP.getPoint(i).getX(), nP.getPoint(i).getY(), nP.getPoint(i).getZ());
            points.push_back(p);
        }
        // define polyhedron to hold convex hull
        Surface_mesh sm;
        CGAL::convex_hull_3(points.begin(), points.end(), sm);

        //iterate each edge of the convex hull
        for (auto e : edges(sm)) {
            //get the two vertices of the edge
            auto v1 = sm.vertex(e, 0);
            auto v2 = sm.vertex(e, 1);
            //get the points
            Point_3 p1 = sm.point(v1);
            Point_3 p2 = sm.point(v2);

            Vect3d vec1(p1.x(), p1.y(), p1.z());
            Vect3d vec2(p2.x(), p2.y(), p2.z());
            //create a segment
            Segment3d s(vec1, vec2);
            //add the segment to the list of segments
            segments.push_back(s);
        }
    }
    else {
        typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
        typedef K::Point_2 Point_2;
        typedef std::vector<Point_2> Point_vector;

        std::vector<Point_2> points;
        Point_2 p;
        for (int i = 0; i < nP.size(); i++) {
            p = Point_2(nP.getPoint(i).getX(), nP.getPoint(i).getY());
            points.push_back(p);
        }
        // define polyhedron to hold convex hull
        Point_vector convex_hull;
        CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(convex_hull));


        for (auto v : convex_hull) {
            Point_2 p = v;
            Vect2d v2d(p.x(), p.y());
            puntos2D.push_back(v2d);
        }
    }


}

const std::vector<Vect3d>& ConvexHull::getPuntos3D() const {
    return puntos;
}

const std::vector<Vect2d>& ConvexHull::getPuntos2D() const {
    return puntos2D;
}

const std::vector<Segment3d> &ConvexHull::getSegments() const {
    return segments;
}

const std::vector<Triangle3d> &ConvexHull::getTriangulos() const {
    return triangulos;
}
