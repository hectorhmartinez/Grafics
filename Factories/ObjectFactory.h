#pragma once


#include "Modelling/Objects/Mesh.h"
#include "Modelling/Objects/Plane.h"


class ObjectFactory
{
    ObjectFactory(){};

public:

    static ObjectFactory& getInstance() {
        static ObjectFactory instance;
        return instance;
    }

    shared_ptr<Mesh> createObject(QString s);

    // Crea un objecte gizmo per una data concreta
    // FASE 2: Cal incloure la translació i l'escalat per a poder escalar l'objecte sogon el valor de la dada
    shared_ptr<Mesh> createObject( vector<vec3>points,QString s, float data);
    shared_ptr<Mesh> createPlane(vector<vec3>points);

};


