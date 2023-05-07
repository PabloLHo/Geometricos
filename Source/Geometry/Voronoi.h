#pragma once
#include "PointCloud3d.h"
#include "SegmentLine.h"



class Voronoi
{

private:

	std::vector<std::pair<SegmentLine*, bool>> ejes;

public:
	Voronoi();
	~Voronoi();

	Voronoi(PointCloud3d* nube);

	std::vector<std::pair<SegmentLine*, bool>> getEjes() { return ejes; };

	std::pair<SegmentLine*, bool> getEje(int i) { return ejes[i]; };

};