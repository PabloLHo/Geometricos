#include "stdafx.h"
#include "SceneContent.h"

#include "ChronoUtilities.h"
#include "InclDraw2D.h"
#include "InclGeom2D.h"
#include "InclGeom3D.h"
#include "InclDraw3D.h"

#include "RandomUtilities.h"


// ----------------------------- BUILD YOUR SCENARIO HERE -----------------------------------

void AlgGeom::SceneContent::buildScenario()
{
    vec3 minBoundaries = vec3(-3.0f, -.4, -3.0f), maxBoundaries = vec3(-minBoundaries);

    // Mesh
    TriangleModel* triangleModel = new TriangleModel("Assets/Models/Ajax.obj");
    auto model = (new DrawMesh(*triangleModel))->overrideModelName();
    this->addNewModel(model);

    // Voxelization
    //const vec3& voxelSize = vec3(0.05f);
    //ChronoUtilities::initChrono();
    //std::cout << "Inicio voxelizacion " << std::endl;
    //Voxelization* voxelization = new Voxelization(triangleModel, voxelSize, 1);
    //std::cout << "Voxelization latency: " << ChronoUtilities::getDuration() << std::endl;


    //PRACTICA 5

        //PRUEBA 5.A
    //std::vector<Vect3d> points;
    //for (int i = 0; i < 100; i++) {
    //    Vect3d point(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x),
    //        RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y), 0);
    //    points.push_back(point);
    //}
    //PointCloud3d nubeP(points);
    //this->addNewModel((new DrawPointCloud(nubeP))->overrideModelName());
    
    //ConvexHull envolventeConvexa(nubeP, 0);

    //for (int i = 0; i < envolventeConvexa.getPuntos2D().size(); i++) {
    //    SegmentLine *segmento = new SegmentLine(envolventeConvexa.getPuntos2D()[i], envolventeConvexa.getPuntos2D()[(i + 1) % envolventeConvexa.getPuntos2D().size()]);
    //    this->addNewModel((new DrawSegment(*segmento))->overrideModelName()->setLineColor(vec3(1, 0, 0)));
    //    delete segmento;
    //}

    ConvexHull envolventeModelo("Assets/Models/Ajax.obj");

    int tam = envolventeModelo.getSegments().size();
    for (int i = 0; i < tam; i++) {
        Segment3d aux = envolventeModelo.getSegments()[i];
        this->addNewModel((new DrawSegment(aux))->overrideModelName());
    }

    //int tam = envolventeModelo.getTriangulos().size();
    //for (int i = 0; i < tam; i++) {
    //    Triangle3d aux = envolventeModelo.getTriangulos()[i];
    //    this->addNewModel((new DrawTriangle(aux))->overrideModelName());
    //}

    //Práctica 5.B


    //DelaunayTriangulation triangulacion(&nubeP);

    //for (int i = 0; i < triangulacion.getCaras().size(); i++) {
    //    this->addNewModel((new DrawTriangle(*triangulacion.getCara(i)))->overrideModelName()->setLineColor(vec3(1, 0, 0)));
    //}

    //Voronoi diagramaV(&nubeP);

    //for (int i = 0; i < diagramaV.getEjes().size(); i++) {
    //    if (diagramaV.getEje(i).second) {
    //        this->addNewModel((new DrawSegment(*diagramaV.getEje(i).first))->overrideModelName()->setLineColor(vec3(1, 0, 0))->setPointColor(vec3(1, 0, 0)));
    //    }
    //    else {
    //        RayLine rayo(diagramaV.getEje(i).first->getA(), diagramaV.getEje(i).first->getB());
    //        this->addNewModel((new DrawRay(rayo))->overrideModelName()->setLineColor(vec3(1, 0, 0))->setPointColor(vec3(1, 0, 0)));
    //    }

    //}
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
