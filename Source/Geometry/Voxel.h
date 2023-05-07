#pragma once
#include "vector"
#include "iostream"
#include "Vect3d.h"
#include "Triangle3d.h"
using namespace std;

enum Formato_Voxel {
	GRIS,
	BLANCO,
	NEGRO,
	NP
};


class Voxel
{
private:
	Formato_Voxel formatin;
	vector <Vect3d> puntos;
	Vect3d centro, min, max;
	vec3 tam;

public:
	Voxel();
	~Voxel();
	Voxel(const Voxel& v);
	Voxel(Vect3d puntoMin, vec3 tamVoxel);
	void inserta(Vect3d punto);
	bool busca(Vect3d punto);
	bool borra(Vect3d punto);

	void setFormato(Formato_Voxel formato) { formatin = formato; };

	Vect3d getMin() { return this->min; };
	Vect3d getMax() { return this->max; };
	Formato_Voxel getFormato() { return this->formatin; };

	bool fuerzaBruta(Triangle3d triangulo);
	bool lineaBarrido(Triangle3d triangulo);
	bool aabb_tri(Triangle3d triangulo);

	bool planeBoxOverlap(Vect3d normal, Vect3d vert, vec3 maxBox);
	bool triBoxOverlap(Vect3d centro, vec3 tam, std::vector<Vect3d> vertices);

	bool axisTestX(double& a, double& b, float& fa, float& fb, float& p0, float& px, Vect3d& v0, Vect3d& vx, vec3& boxHalfSize, float& min, float& max, float& rad);
	bool axisTestY(double& a, double& b, float& fa, float& fb, float& p0, float& px, Vect3d& v0, Vect3d& vx, vec3& boxHalfSize, float& min, float& max, float& rad);
	bool axisTestZ(double& a, double& b, float& fa, float& fb, float& p0, float& px, Vect3d& v0, Vect3d& vx, vec3& boxHalfSize, float& min, float& max, float& rad);

};

