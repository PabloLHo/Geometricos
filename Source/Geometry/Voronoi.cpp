#include "stdafx.h"
#include "Voronoi.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

Voronoi::Voronoi() {

}

Voronoi::~Voronoi() {

}

Voronoi::Voronoi(PointCloud3d* nube) {
	typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
	typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
	typedef Triangulation::Edge_iterator  Edge_iterator;
	typedef Triangulation::Point          Point;

	Triangulation T;
	
	for (int i = 0; i < nube->size(); i++) {
		Point p(nube->getPoint(i).getX(), nube->getPoint(i).getY());
		T.insert(p);
	}

	int ns = 0;
	int nr = 0;
	Edge_iterator eit = T.edges_begin();
	for (; eit != T.edges_end(); ++eit) {
		CGAL::Object o = T.dual(eit);
		if (CGAL::object_cast<K::Segment_2>(&o)) { 
			Vect2d origen(CGAL::object_cast<K::Segment_2>(&o)->source().x(), CGAL::object_cast<K::Segment_2>(&o)->source().y());
			Vect2d destino(CGAL::object_cast<K::Segment_2>(&o)->target().x(), CGAL::object_cast<K::Segment_2>(&o)->target().y());
			ejes.push_back(std::pair(new SegmentLine(origen, destino), true));
		}
		else if (CGAL::object_cast<K::Ray_2>(&o)) {
			Vect2d origen(CGAL::object_cast<K::Ray_2>(&o)->source().x(), CGAL::object_cast<K::Ray_2>(&o)->source().y());
			Vect2d destino(CGAL::object_cast<K::Ray_2>(&o)->source().x() + CGAL::object_cast<K::Ray_2>(&o)->direction().dx() * 1000
				, CGAL::object_cast<K::Ray_2>(&o)->source().y() + CGAL::object_cast<K::Ray_2>(&o)->direction().dy() * 1000);
			ejes.push_back(std::pair(new SegmentLine(origen,destino), false));
		}
	}

}
