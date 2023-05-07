#include "stdafx.h"
#include "BasicGeometry.h"
#include "Triangle3d.h"
#include "Edge3d.h"


Triangle3d::Triangle3d()
{
}

Triangle3d::Triangle3d(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz)
	: _a(ax, ay, az), _b(bx, by, bz), _c(cx, cy, cz)
{
}

Triangle3d::Triangle3d(const Triangle3d & triangle)
	: _a(triangle._a), _b(triangle._b), _c(triangle._c)
{
}

Triangle3d::Triangle3d(Vect3d & va, Vect3d & vb, Vect3d & vc)
	: _a(va), _b(vb), _c(vc)
{
}

Triangle3d::~Triangle3d()
{
}

double Triangle3d::area()
{
	Vect3d v1(_b.sub(_a));
	Vect3d v2(_c.sub(_a));
	Vect3d pv(v1.xProduct(v2));

	return pv.module() / 2;
}

Triangle3d::PointPosition Triangle3d::classify(Vect3d& point)
{
	Vect3d a = this->getA();
	Vect3d aux = point.sub(a);
	Vect3d* v = new Vect3d(aux);
	double len = v->module();
	if (BasicGeometry::equal(0.0, len)) {
		return PointPosition::COPLANAR;
	}
	v = new Vect3d(v->scalarMul(1 / len));
	Vect3d normal = this->normal();
	double d = v->dot(normal);
	if (BasicGeometry::equal(0.0, d)) {
		return PointPosition::COPLANAR;
	}
	else if (d < 0.0) {
		return PointPosition::NEGATIVE;
	}

	return PointPosition::POSITIVE;
}

Vect3d Triangle3d::normal()
{
	Vect3d v1 (_b.sub(_a));
	Vect3d v2 (_c.sub(_a));
	Vect3d n (v1.xProduct(v2));
	double module = n.module();

	return (n.scalarMul(1.0f / module));
}

Triangle3d & Triangle3d::operator=(const Triangle3d & triangle)
{
	_a = triangle._a;
	_b = triangle._b;
	_c = triangle._c;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Triangle3d& triangle)
{
	std::cout << "Triangle 3D -> " << triangle._a << ", " << triangle._b << ", " << triangle._c;
	return os;
}

void Triangle3d::set(Vect3d & va, Vect3d & vb, Vect3d & vc)
{
	_a = va;
	_b = vb;
	_c = vc;
}

AABB Triangle3d::getAABB() {

	float minX, minY, minZ, maxX, maxY, maxZ;
	maxX = BasicGeometry::max3(getA().getX(), getB().getX(), getC().getX());
	minX = BasicGeometry::min3(getA().getX(), getB().getX(), getC().getX());
	maxY = BasicGeometry::max3(getA().getY(), getB().getY(), getC().getY());
	minY = BasicGeometry::min3(getA().getY(), getB().getY(), getC().getY());
	maxZ = BasicGeometry::max3(getA().getZ(), getB().getZ(), getC().getZ());
	minZ = BasicGeometry::min3(getA().getZ(), getB().getZ(), getC().getZ());

	Vect3d min(minX, minY, minZ);
	Vect3d max(maxX, maxY, maxZ);
	return AABB(min, max);
}


bool Triangle3d::ray_tri(Ray3d& rayo, Vect3d& p) {

	Vect3d aux = getA();
	Vect3d e1 = getB().sub(aux);
	Vect3d e2 = getC().sub(aux);

	Vect3d pvec = rayo.getDirection().xProduct(e2);
	float det = e1.dot(pvec);

	if (det < BasicGeometry::EPSILON && det > -BasicGeometry::EPSILON) return false;

	float f = 1.0 / det;
	Vect3d tvec = rayo.getOrigin().sub(aux);
	float u = f * tvec.dot(pvec);
	if (u < 0.0f || u > 1) return false;

	Vect3d qvec = tvec.xProduct(e1);
	float v = f * rayo.getDirection().dot(qvec);
	if (v < 0.0f || u + v > 1) return false;

	float t = f * e2.dot(qvec) ;
	if (t > BasicGeometry::EPSILON) {
		aux = rayo.getDirection().scalarMul(t);
		p = rayo.getOrigin().add(aux);
		return true;
	}
	else {
		return false;
	}
	
}