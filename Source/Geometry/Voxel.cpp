#include "stdafx.h"
#include "Voxel.h"
#include "BasicGeometry.h"
#include "ChronoUtilities.h"


Voxel::Voxel() {
    formatin = Formato_Voxel::NP;
    puntos = vector<Vect3d>();
}

Voxel::Voxel(Vect3d puntoMin, vec3 tam) {
    formatin = Formato_Voxel::NP;
    
    Vect3d aux(puntoMin.getX() + tam[0] / 2, puntoMin.getY() + tam[1] / 2, puntoMin.getZ() + tam[2] / 2);
    centro = aux;
    this->min = puntoMin;
    Vect3d aux2(min.getX() + tam[0], min.getY() + tam[1], min.getZ() + tam[2]);
    this->max = aux2;
    this->tam = tam;

}

Voxel::Voxel(const Voxel& v) {
    formatin = v.formatin;
    puntos = v.puntos;
}


Voxel::~Voxel() {

}

void Voxel::inserta(Vect3d punto) {
    puntos.insert(puntos.end(), punto);
}

bool Voxel::busca(Vect3d punto) {
    for (int i = 0; i < puntos.size(); i++) {
        if (puntos[i] == punto) {
            return true;
        }
    }
    return false;
}

bool Voxel::borra(Vect3d punto) {
    vector<Vect3d>::iterator it = puntos.begin();
    while (it != puntos.end()) {
        if (*it == punto) {
            puntos.erase(it);
            return true;
        }
    }
    return false;
}

bool Voxel::fuerzaBruta(Triangle3d t) {
    std::vector<Vect3d> vertices;
    vertices.push_back(t.getA());
    vertices.push_back(t.getB());
    vertices.push_back(t.getC());
    vec3 halfsize(tam[0] / 2, tam[1] / 2, tam[2] / 2);
    if (triBoxOverlap(this->centro, halfsize, vertices)) {
        return true;
    }
    return false;
}



bool Voxel::planeBoxOverlap(Vect3d normal, Vect3d vert, vec3 maxbox)    // -NJMP-

{

    Vect3d vmin, vmax, v;

    v = vert;                    // -NJMP-

    if (normal.getX() > 0.0f)

    {

        vmin.setX(-maxbox[0] - v.getX());    // -NJMP-

        vmax.setX(maxbox[0] - v.getX());    // -NJMP-

    }

    else

    {

        vmin.setX(maxbox[0] - v.getX());    // -NJMP-

        vmax.setX(-maxbox[0] - v.getX());    // -NJMP-

    }

    if (normal.getY() > 0.0f)

    {

        vmin.setY(-maxbox[1] - v.getY());    // -NJMP-

        vmax.setY(maxbox[1] - v.getY());    // -NJMP-

    }

    else

    {

        vmin.setY(maxbox[1] - v.getY());    // -NJMP-

        vmax.setY(-maxbox[1] - v.getY());    // -NJMP-

    }

    if (normal.getZ() > 0.0f)

    {

        vmin.setZ(-maxbox[2] - v.getZ());    // -NJMP-

        vmax.setZ(maxbox[2] - v.getZ());    // -NJMP-

    }

    else

    {

        vmin.setZ(maxbox[2] - v.getZ());    // -NJMP-

        vmax.setZ(-maxbox[2] - v.getZ());    // -NJMP-

    }



    if (normal.dot(vmin) > 0.0f) return 0;    // -NJMP-

    if (normal.dot(vmax) >= 0.0f) return 1;    // -NJMP-



    return 0;

}

bool Voxel::axisTestX(double& a, double& b, float& fa, float& fb, float& p0, float& px, Vect3d& v0, Vect3d& vx, vec3& boxHalfSize, float& min, float& max, float& rad) {
    p0 = a * v0.getY() - b * v0.getZ();

    px = a * vx.getY() - b * vx.getZ();			       	   

    if (p0 < px) { min = p0; max = px; }
    else { min = px; max = p0; }

    rad = fa * boxHalfSize[1] + fb * boxHalfSize[2];

    if (min > rad || max < -rad) return 0;
}

bool Voxel::axisTestY(double& a, double& b, float& fa, float& fb, float& p0, float& px, Vect3d& v0, Vect3d& vx, vec3& boxHalfSize, float& min, float& max, float& rad) {
    p0 = -a * v0.getX() + b * v0.getZ();

    px = -a * vx.getX() + b * vx.getZ();

    if (p0 < px) { min = p0; max = px; }
    else { min = px; max = p0; }

    rad = fa * boxHalfSize[0] + fb * boxHalfSize[2];

    if (min > rad || max < -rad) return 0;
}

bool Voxel::axisTestZ(double& a, double& b, float& fa, float& fb, float& p0, float& px, Vect3d& v0, Vect3d& vx, vec3& boxHalfSize, float& min, float& max, float& rad) {
    p0 = a * v0.getX() - b * v0.getY();

    px = a * vx.getX() - b * vx.getY();

    if (p0 < px) { min = p0; max = px; }
    else { min = px; max = p0; }

    rad = fa * boxHalfSize[0] + fb * boxHalfSize[1];

    if (min > rad || max < -rad) return 0;
}


bool Voxel::triBoxOverlap(Vect3d centro, vec3 tam, std::vector<Vect3d> vertices)

{



    /*    use separating axis theorem to test overlap between triangle and box */

    /*    need to test for overlap in these directions: */

    /*    1) the {x,y,z}-directions (actually, since we use the AABB of the triangle */

    /*       we do not even need to test these) */

    /*    2) normal of the triangle */

    /*    3) crossproduct(edge from tri, {x,y,z}-directin) */

    /*       this gives 3x3=9 more tests */

    Vect3d v0, v1, v2;

    //   float axis[3];

    float min, max, p0, p1, p2, rad, fex, fey, fez;		// -NJMP- "d" local variable removed

    Vect3d normal, e0, e1, e2;



    /* This is the fastest branch on Sun */

    /* move everything so that the boxcenter is in (0,0,0) */
    v0 = vertices[0].sub(centro);

    v1 = vertices[1].sub(centro);

    v2 = vertices[2].sub(centro);



    /* compute triangle edges */
    e0 = v1.sub(v0);

    e1 = v2.sub(v1);

    e2 = v0.sub(v2);



    /* Bullet 3:  */

    /*  test the 9 tests first (this was faster) */
    fex = glm::abs(e0.getX());

    fey = glm::abs(e0.getY());

    fez = glm::abs(e0.getZ());

    double aux = e0.getZ();
    double aux2 = e0.getY();
    double aux3 = e0.getX();

    axisTestX(aux,aux2, fez, fey, p0, p2, v0, v2, tam, min, max, rad);
    axisTestY(aux, aux3, fez, fex, p0, p2, v0, v2, tam, min, max, rad);
    axisTestZ(aux2, aux3, fey, fez, p2, p1, v1, v2, tam, min, max, rad);


    fex = glm::abs(e1.getX());

    fey = glm::abs(e1.getY());

    fez = glm::abs(e1.getZ());

    aux = e1.getZ();
    aux2 = e1.getY();
    aux3 = e1.getX();

    axisTestX(aux, aux2, fez, fey, p0, p2, v0, v2, tam, min, max, rad);
    axisTestY(aux, aux3, fez, fex, p0, p2, v0, v2, tam, min, max, rad);
    axisTestZ(aux2, aux3, fey, fez, p0, p1, v0, v1, tam, min, max, rad);


    fex = glm::abs(e2.getX());

    fey = glm::abs(e2.getY());

    fez = glm::abs(e2.getZ());

    aux = e2.getZ();
    aux2 = e2.getY();
    aux3 = e2.getX();

    axisTestX(aux, aux2, fez, fey, p0, p1, v0, v1, tam, min, max, rad);
    axisTestY(aux, aux3, fez, fex, p0, p1, v0, v1, tam, min, max, rad);
    axisTestZ(aux2, aux3, fey, fez, p2, p1, v1, v2, tam, min, max, rad);



    /* Bullet 1: */

    /*  first test overlap in the {x,y,z}-directions */

    /*  find min, max of the triangle each direction, and test for overlap in */

    /*  that direction -- this is equivalent to testing a minimal AABB around */

    /*  the triangle against the AABB */



    /* test in X-direction */
    min = BasicGeometry::min3(v0.getX(), v1.getX(), v2.getX());
    max = BasicGeometry::max3(v0.getX(), v1.getX(), v2.getX());

    if (min > tam[0] || max < -tam[0]) return 0;



    /* test in Y-direction */
    min = BasicGeometry::min3(v0.getY(), v1.getY(), v2.getY());
    max = BasicGeometry::max3(v0.getY(), v1.getY(), v2.getY());

    if (min > tam[1] || max < -tam[1]) return 0;



    /* test in Z-direction */
    
    min = BasicGeometry::min3(v0.getZ(), v1.getZ(), v2.getZ());
    max = BasicGeometry::max3(v0.getZ(), v1.getZ(), v2.getZ());

    if (min > tam[2] || max < -tam[2]) return 0;



    /* Bullet 2: */

    /*  test if the box intersects the plane of the triangle */

    /*  compute plane equation of triangle: normal*x+d=0 */
    normal = e0.xProduct(e1);

    // -NJMP- (line removed here)

    if (!planeBoxOverlap(normal, v0, tam)) return 0;	// -NJMP-



    return 1;   /* box and triangle overlaps */

}


