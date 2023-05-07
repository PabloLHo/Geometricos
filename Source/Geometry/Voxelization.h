#pragma once
#include "DrawVoxelization.h"
#include "TriangleModel.h"
#include "Voxel.h"





/*
 * File:   Voxelization.h
 * Author: Pablo y Julian
 *
 * Created on 7 de marzo de 2023
 */

class Voxelization
{

	private:
		vec3 tam;
		std::vector<std::vector<std::vector<Voxel*>>> voxeles;
		float xmax, ymax, zmax, xmin, ymin, zmin;
		int numX, numY, numZ;

		bool comprobarPertenencia(Voxel* v, Voxelization* voxelizacion, int &x, int &y, int &z);

	public:
		Voxelization();
		Voxelization(const Voxelization& voxel);
		Voxelization(float _xmax, float _ymax, float _zmax, float _xmin, float _ymin, float _zmin, vec3 _tam);
		Voxelization(TriangleModel *modelo, vec3 tam, int tipo);
		virtual ~Voxelization();

		Voxel* obtenerVoxel(double x, double y, double z);
		void insertar(Vect3d dato);
		void lineaBarrido(std::vector<Triangle3d> triangulos);
		static bool comp(const std::pair<Vect3d, int>& v1, const std::pair<Vect3d, int>& v2);
		std::vector<Voxel*> obtenerVoxeles(AABB aabb_ti);
		std::vector<std::vector<std::vector<Voxel*>>> getVoxeles() { return voxeles; };

		bool rayTraversal(Ray3d& r, std::vector<Voxel*>& v);
		bool rayBoxIntersection(Ray3d& r, float& tMin, float& tMax,float t0, float t1);

		bool insideVoxel(Voxel *v, Vect3d vertice);

		AlgGeom::DrawVoxelization* getRenderingObject(bool algo);

		float getXMax() { return xmax; };
		float getYMax() { return ymax; };
		float getZMax() { return zmax; };
		float getXMin() { return xmin; };
		float getYMin() { return ymin; };
		float getZMin() { return zmin; };
		vec3 getTam() { return tam; };

		Voxelization* AND(Voxelization &v);
		Voxelization* OR(Voxelization& v);
		Voxelization* XOR(Voxelization& v);

	protected:
		void flood();
		void recursivo(Voxel *v, int x, int y, int z);
};

