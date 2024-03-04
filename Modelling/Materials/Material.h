#pragma once

#include <vector>
#include <memory>

#include <library/Common.h>
#include <library/vec.h>

#include <QGLShaderProgram>
#include <QRegularExpression>

using namespace std;
using namespace Common;
// TO DO: A canviar a la fase 1 de la practica 2
// Classe que representa els materials d'un objecte
class Material {


public:
    Material();
    Material(vec3 a, vec3 d, vec3 s,vec3 t, float shin);
    void toGPU(shared_ptr<QGLShaderProgram> program);



protected:
    vec3 Ka, Kd, Ks, Kt;
    float shininess;
};

