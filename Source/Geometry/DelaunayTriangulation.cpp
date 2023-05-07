#include "stdafx.h"
#include "DelaunayTriangulation.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>



DelaunayTriangulation::DelaunayTriangulation() {

}

DelaunayTriangulation::~DelaunayTriangulation() {

}

DelaunayTriangulation::DelaunayTriangulation(PointCloud3d* nube) {
	typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
	typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
	typedef K::Point_2 Point_2;

	Delaunay triangulation;
	for (int i = 0; i < nube->size(); i++) {
		Point_2 p(nube->getPoint(i).getX(), nube->getPoint(i).getY());
		triangulation.insert(p);
	}

	for (Delaunay::Finite_faces_iterator it = triangulation.finite_faces_begin(); it != triangulation.finite_faces_end(); ++it) {
		Vect2d p(it->vertex(0)->point().x(), it->vertex(0)->point().y());
		Vect2d p1(it->vertex(1)->point().x(), it->vertex(1)->point().y());
		Vect2d p2(it->vertex(2)->point().x(), it->vertex(2)->point().y());
		caras.push_back(new Triangle(p, p1, p2));
	}
}
