#pragma once
#include "PointCloud3d.h"
#include "Triangle.h"



class DelaunayTriangulation
{

private:
	std::vector<Triangle*> caras;

public:
	DelaunayTriangulation();
	~DelaunayTriangulation();

	DelaunayTriangulation(PointCloud3d* nube);

	std::vector<Triangle*> getCaras() { return caras; };
	Triangle* getCara(int i) { return caras[i]; };

};

