#include "stdafx.h"
#include "SceneContent.h"

#include "ChronoUtilities.h"
#include "InclDraw2D.h"
#include "InclGeom2D.h"
#include "InclGeom3D.h"
#include "InclDraw3D.h"
#include "PointCloud.h"
#include "RandomUtilities.h"


// ----------------------------- BUILD YOUR SCENARIO HERE -----------------------------------

void AlgGeom::SceneContent::buildScenario()
{
    vec3 minBoundaries = vec3(-3.0f, -.4, -3.0f), maxBoundaries = vec3(-minBoundaries);

    //// Random segments
    //int numSegments = 8;

    //for (int segmentIdx = 0; segmentIdx < numSegments; ++segmentIdx)
    //{
    //    Vect3d a(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y), RandomUtilities::getUniformRandom(minBoundaries.z, maxBoundaries.z));
    //    Vect3d b(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y), RandomUtilities::getUniformRandom(minBoundaries.z, maxBoundaries.z));
    //    Segment3d* segment = new Segment3d(a, b);

    //    this->addNewModel((new DrawSegment(*segment))->setLineColor(RandomUtilities::getUniformRandomColor())->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));
    //    delete segment;
    //}

    //// Random points
    //int numPoints = 100;

    //for (int pointIdx = 0; pointIdx < numPoints; ++pointIdx)
    //{
    //    Point point(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x));
    //    this->addNewModel((new DrawPoint(point))->setPointColor(RandomUtilities::getUniformRandomColor())->overrideModelName()->setPointSize(RandomUtilities::getUniformRandom(4.0f, 8.0f)));
    //}

    //// Random triangles
    //int numTriangles = 30;
    //float alpha = 2 * glm::pi<float>() / static_cast<float>(numTriangles);

    //for (int triangleIdx = 0; triangleIdx < numTriangles; ++triangleIdx)
    //{
    //    float rand_b = RandomUtilities::getUniformRandom(.9f, 1.3f), rand_c = RandomUtilities::getUniformRandom(.8f, 1.4f);
    //    Vect3d a(.0f, .0f, .0f);
    //    Vect3d b(glm::cos(alpha * triangleIdx) * rand_b, glm::sin(alpha * triangleIdx) * rand_b, RandomUtilities::getUniformRandom(-.1f, .1f));
    //    Vect3d c(glm::cos(alpha * (triangleIdx + 1)) * rand_c, glm::sin(alpha * (triangleIdx + 1)) * rand_c, RandomUtilities::getUniformRandom(-.1f, .1f));
    //    Triangle3d* triangle = new Triangle3d(a, b, c);

    //    this->addNewModel((new DrawTriangle(*triangle))->setLineColor(RandomUtilities::getUniformRandomColor())->setTriangleColor(vec4(RandomUtilities::getUniformRandomColor(), 1.0f))
    //        ->overrideModelName());
    //    delete triangle;
    //}

    //// Point cloud
    //PointCloud3d* pointCloud = new PointCloud3d(numPoints * 10, maxBoundaries.y * 6.0f);
    //this->addNewModel((new DrawPointCloud(*pointCloud))->setPointColor(RandomUtilities::getUniformRandomColor())->overrideModelName()->setPointSize(RandomUtilities::getUniformRandom(4.0f, 8.0f)));
    //delete pointCloud;

    //// Mesh
    //TriangleModel* triangleModel = new TriangleModel("Assets/Models/Ajax.obj");
    //auto model = (new DrawMesh(*triangleModel))->setModelMatrix(glm::translate(mat4(1.0f), vec3(.0f, .0f, .8f)))->overrideModelName();
    //this->addNewModel(model);

    //// AABB
    //AABB aabb(Vect3d(-1.0f, -2.0f, -1.5f), Vect3d(2.0f, 3.0f, 1.0f));
    //this->addNewModel((new DrawAABB(aabb))->overrideModelName());

    //Prueba 2.A
    int numPoints = 50;
    PointCloud3d* pointCloud = new PointCloud3d(numPoints, maxBoundaries.y * 6.0f);
    this->addNewModel((new DrawPointCloud(*pointCloud))->setPointColor(RandomUtilities::getUniformRandomColor())->overrideModelName()->setPointSize(RandomUtilities::getUniformRandom(4.0f, 8.0f)));
    
    Vect3d a(pointCloud->getPoint(RandomUtilities::getUniformRandomInt(0, numPoints - 1)));
    Vect3d b(pointCloud->getPoint(RandomUtilities::getUniformRandomInt(0, numPoints - 1)));

    Line3d* recta = new Line3d(a, b);
    vec3 color(1, 0, 0);
    this->addNewModel((new DrawLine(*recta))->setLineColor(color)->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));

    Vect3d c(pointCloud->getPoint(RandomUtilities::getUniformRandomInt(0, numPoints - 1)));
    Vect3d d(pointCloud->getPoint(RandomUtilities::getUniformRandomInt(0, numPoints - 1)));
    
    Line3d* recta_2 = new Line3d(c,d);
    vec3 color2(0, 1, 0);
    this->addNewModel((new DrawLine(*recta_2))->setLineColor(color2)->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));

    if (recta->isParallel(*recta_2)) {
        std::cout << "Las rectas son paralelas" << std::endl;
    }
    else {
        std::cout << "Las rectas no son paralelas" << std::endl;
    }

    Vect3d e(pointCloud->getPoint(RandomUtilities::getUniformRandomInt(0, numPoints - 1)));
    Vect3d f(pointCloud->getPoint(RandomUtilities::getUniformRandomInt(0, numPoints - 1)));

    Segment3d* segment = new Segment3d(e,f);
    vec3 colorSegment(1, 1, 1);
    this->addNewModel((new DrawSegment(*segment))->setLineColor(colorSegment)->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));
    

    Vect3d g(pointCloud->getPoint(RandomUtilities::getUniformRandomInt(0, numPoints - 1)));
    Vect3d h(pointCloud->getPoint(RandomUtilities::getUniformRandomInt(0, numPoints - 1)));

    Ray3d* ray = new Ray3d(g, h);
    vec3 colorRayo(0, 0, 1);
    this->addNewModel((new DrawRay(*ray))->setLineColor(colorRayo)->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));
    
    int indice = 0;
    float distancia = FLT_MIN;
    for (int i = 0; i < numPoints; i++) {
        Vect3d punto(pointCloud->getPoint(i));
        if (recta->distance(punto) > distancia) {
            indice = i;
            distancia = recta->distance(punto);
        }
    }

    Vect3d punto(pointCloud->getPoint(indice));
    Line3d* recta_3 = new Line3d(recta->normalLine(punto));
    vec3 color3(1, 1, 0);
    this->addNewModel((new DrawLine(*recta_3))->setLineColor(color3)->overrideModelName()->setLineWidth(RandomUtilities::getUniformRandom(1.0f, 3.0f)));

    if (recta->isPerpendicular(*recta_3)) {
        std::cout << "Las rectas son perpendiculares" << std::endl;
    }
    else {
        std::cout << "Las rectas no son perpendiculares" << std::endl;
    }

    distancia = recta->distance(*recta_2);
    std::cout << "La distancia de las dos primeras rectas es: " << distancia << std::endl;

    AABB* pc_aabb = new AABB(pointCloud->getAABB());
    this->addNewModel((new DrawAABB(*pc_aabb))->overrideModelName());

    Vect3d min1(pc_aabb->getMin());
    Vect3d min2(pc_aabb->getMax().getX(), pc_aabb->getMin().getY(), pc_aabb->getMin().getZ());
    Vect3d min3(pc_aabb->getMax().getX(), pc_aabb->getMin().getY(), pc_aabb->getMax().getZ());
    Plane* plano_inferior = new Plane(min1, min2, min3, true);
    this->addNewModel((new DrawPlane(*plano_inferior))->overrideModelName()->setLineWidth(5.0)->setLineColor(vec3(1,1,1)));



    //Prueba 2.B
    Vect3d point(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y), RandomUtilities::getUniformRandom(minBoundaries.z, maxBoundaries.z));
    Vect3d point2(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y), RandomUtilities::getUniformRandom(minBoundaries.z, maxBoundaries.z));
    Vect3d point3(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y), RandomUtilities::getUniformRandom(minBoundaries.z, maxBoundaries.z));
    Plane* plano_aleatorio = new Plane(point,point2,point3, true);
    this->addNewModel((new DrawPlane(*plano_aleatorio))->overrideModelName());

    Vect3d punto_equi1(segment->getOrigin());
    Vect3d punto_equi2(segment->getDestination());

    Vect3d normal_plane;
    float d_plane;
    punto_equi1.getPlane(punto_equi2, normal_plane, d_plane);
    Vect3d punto1(0, 0, - d_plane / normal_plane.getZ());
    Vect3d punto2(-d_plane / normal_plane.getX(), 0, 0);
    Vect3d punto3(0, -d_plane / normal_plane.getY(), 0);
    Plane* plane_2 = new Plane(punto1, punto2, punto3, true);
    
    Line3d intersect;

    if (plano_aleatorio->intersect(*plane_2, intersect)) {
        this->addNewModel((new DrawLine(intersect))->overrideModelName()->setLineColor(vec3(1,0,1))->setLineWidth(3.0f));
    }
    else {
        std::cout << "No intersecta" << std::endl;
    }

    Vect3d point_aleatorio(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y), RandomUtilities::getUniformRandom(minBoundaries.z, maxBoundaries.z));
    this->addNewModel((new DrawPoint(point_aleatorio))->setPointColor(vec3(0,0,1))->overrideModelName()->setPointSize(7.0));
    std:: cout << "La distancia del plano aleatorio al punto azul es de: " << plano_aleatorio->distance(point_aleatorio) << std::endl;

    Vect3d equi_3(plano_aleatorio->reflectedPoint(point_aleatorio));
    this->addNewModel((new DrawPoint(equi_3))->setPointColor(vec3(0, 1, 1))->overrideModelName()->setPointSize(7.0));
    std::cout << "La distancia del plano aleatorio al punto azul es de: " << plano_aleatorio->distance(equi_3) << std::endl;


    //Prueba 2.C
    TriangleModel* triangleModel = new TriangleModel("Assets/Models/Ajax.obj");
    auto model = (new DrawMesh(*triangleModel))->setModelMatrix(glm::translate(mat4(1.0f), vec3(.0f, .0f, .8f)))->overrideModelName();
    this->addNewModel(model);

    std::vector<Triangle3d> caras = triangleModel->getFaces();
    std::vector<int> indices;
    std::vector<float> distancias;
    for (int i = 0; i < 6; i++) {
        indices.push_back(0);
        distancias.push_back(FLT_MAX);
    }

    Vect3d plano1(1, 0, 0);
    Vect3d plano2(-1, 0, 0);
    Vect3d plano3(0, 1, 0);
    Vect3d plano4(0, -1, 0);
    Vect3d plano5(0, 0, 1);
    Vect3d plano6(0, 0, -1);

    for (int i = 1; i < caras.size(); i++) {  
        float valor = glm::abs(caras[i].normal().getX() - plano1.getX()) + glm::abs(caras[i].normal().getY() - plano1.getY()) + glm::abs(caras[i].normal().getZ() - plano1.getZ());
        if (distancias[0] > valor ) {
            indices[0] = i;
            distancias[0] = valor;
        }      
        valor = glm::abs(caras[i].normal().getX() - plano2.getX()) + glm::abs(caras[i].normal().getY() - plano2.getY()) + glm::abs(caras[i].normal().getZ() - plano2.getZ());
        if (distancias[1] > valor) {
            indices[1] = i;
            distancias[1] = valor;
        }    
        valor = glm::abs(caras[i].normal().getX() - plano3.getX()) + glm::abs(caras[i].normal().getY() - plano3.getY()) + glm::abs(caras[i].normal().getZ() - plano3.getZ());
        if (distancias[2] > valor) {
            indices[2] = i;
            distancias[2] = valor;
        }        
        valor = glm::abs(caras[i].normal().getX() - plano4.getX()) + glm::abs(caras[i].normal().getY() - plano4.getY()) + glm::abs(caras[i].normal().getZ() - plano4.getZ());
        if (distancias[3] > valor) {
            indices[3] = i;
            distancias[3] = valor;
        }        
        valor = glm::abs(caras[i].normal().getX() - plano5.getX()) + glm::abs(caras[i].normal().getY() - plano5.getY()) + glm::abs(caras[i].normal().getZ() - plano5.getZ());
        if (distancias[4] > valor) {
            indices[4] = i;
            distancias[4] = valor;
        }
        valor = glm::abs(caras[i].normal().getX() - plano6.getX()) + glm::abs(caras[i].normal().getY() - plano6.getY()) + glm::abs(caras[i].normal().getZ() - plano6.getZ());
        if (distancias[5] > valor) {
            indices[5] = i;
            distancias[5] = valor;
        }
    }

    for (int i = 0; i < 6; i++) {
        this->addNewModel((new DrawTriangle(caras[indices[i]]))->setLineColor(vec3(1, 0, 0))->setModelMatrix(glm::translate(mat4(1.0f), vec3(.0f, .0f, .8f))));
    }


    delete segment;
    delete pc_aabb;
    delete recta;
    delete recta_2;
    delete recta_3;
    delete ray;
    delete pointCloud;
    delete plano_inferior;
}

void AlgGeom::SceneContent::buildCamera(uint16_t width, uint16_t height)
{
    Camera* camera = new Camera(width, height, false);
    camera->setPosition(vec3(.0f, .0f, 4.0f));
    camera->setLookAt(vec3(.0f, .0f, 0.0f));
    camera->saveCamera();

    this->_camera.push_back(std::unique_ptr<Camera>(camera));
}


// ------------------------------------------------------------------------------------------


AlgGeom::SceneContent::SceneContent()
{
}

AlgGeom::SceneContent::~SceneContent()
{
	_camera.clear();
	_model.clear();
}

void AlgGeom::SceneContent::addNewCamera(ApplicationState* appState)
{
	_camera.push_back(std::unique_ptr<Camera>(new Camera(appState->_viewportSize.x, appState->_viewportSize.y, true)));
}

void AlgGeom::SceneContent::addNewModel(Model3D* model)
{	
	_model.push_back(std::unique_ptr<Model3D>(model));
}

AlgGeom::Model3D* AlgGeom::SceneContent::getModel(Model3D::Component* component)
{
	for (auto& model : _model)
	{
		if (model->belongsModel(component))
			return model.get();
	}

	return nullptr;
}
