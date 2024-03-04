#include "Modelling/Scene.h"

/**
 * @brief Scene::Scene
 */
Scene::Scene() {
    // Inicialització de la capsa minima
    capsaMinima.pmin = vec3(-1.0, -1.0,-1.0);
    capsaMinima.a = 2;
    capsaMinima.h = 2;
    capsaMinima.p = 2;
    lightAmbientGlobal = vec3(0.2, 0.2, 0.2);
}

/**
 * @brief Scene::~Scene
 */
Scene::~Scene() {
    objects.clear();
    lights.clear();
}

/**
 * @brief Scene::addObject
 * @param obj
 */
void Scene::addObject(shared_ptr<Mesh> obj) {
    objects.push_back(obj);
    calculCapsaMinCont3DEscena();
}

/**
 * @brief Scene::toGPU
 */
void Scene::toGPU(shared_ptr<QGLShaderProgram> p) {
    lightsToGPU(p);
    setAmbientGlobalToGPU(p);
    for(unsigned int i=0; i < objects.size(); i++){
        objects.at(i)->toGPU(p);
    }
}

/**
 * @brief Scene::draw
 */
void Scene::draw() {
    for(unsigned int i=0; i < objects.size(); i++){
        objects.at(i)->draw();
    }
}


/**
 * @brief Scene::getLightActual
 * @return
 */
shared_ptr<Light> Scene::getLightActual() {
    // TO DO OPCIONAL: A modificar si es vol canviar el comportament de la GUI
    // Ara per ara dona com a Light actual la darrera que s'ha inserit
    return (lights[lights.size()-1]);
}

/**
 * @brief Scene::setLightActual
 * @param l
 */
void Scene::setLightActual(shared_ptr<Light> l){
    lights[lights.size()-1]=l;
}



/**
 * @brief Scene::lightsToGPU
 * @param program
 */
void Scene::lightsToGPU(shared_ptr<QGLShaderProgram> program){
// TO DO: A implementar a la fase 1 de la practica 2
    struct LightAtributes
      {
       GLuint type;
       GLuint Ia;
       GLuint Id;
       GLuint Is;
       GLuint coeficients;
       GLuint position;
       GLuint direction;
       GLuint angle;
      };

      // vector de structs gl_IdLights
      LightAtributes gl_IdVect[MAX_LIGHTS];
      for(int i = 0; i < lights.size(); i++){

          cout<<"estic a lightoGPU";
          // variables especifiques per les diferents tipus de llum;
          vec3 position = vec3(0,0,0);
          vec3 coeficients = vec3(0,0,0);
          vec3 direction = vec3(0,0,0);
          float angle = 0;
          LightType tipus = lights[i]->getTipusLight();
          // Diferents tipus de llum
          if (tipus == Direccional){
              shared_ptr<DirectionalLight> dirrecional = dynamic_pointer_cast<DirectionalLight> (lights[i]);
              direction = dirrecional->getLightDirection();
          }else if (tipus == Spot){
              shared_ptr<SpotLight> spot = dynamic_pointer_cast<SpotLight> (lights[i]);
              direction = spot->getLightDirection();
              angle = spot->getAngle();
          }

          gl_IdVect[i].type = program->uniformLocation(QString("lights[%1].type").arg(i));
          gl_IdVect[i].Ia = program->uniformLocation(QString("lights[%1].Ia").arg(i));
          gl_IdVect[i].Id = program->uniformLocation(QString("lights[%1].Id").arg(i));
          gl_IdVect[i].Is = program->uniformLocation(QString("lights[%1].Is").arg(i));
          gl_IdVect[i].coeficients = program->uniformLocation(QString("lights[%1].coeficients").arg(i));
          gl_IdVect[i].position = program->uniformLocation(QString("lights[%1].position").arg(i));
          gl_IdVect[i].direction = program->uniformLocation(QString("lights[%1].direction").arg(i));
          gl_IdVect[i].angle = program->uniformLocation(QString("lights[%1].angle").arg(i));


          glUniform1i(gl_IdVect[i].type,lights.at(i)->getTipusLight());
          glUniform3fv(gl_IdVect[i].Ia,1,lights.at(i)->getIa());
          glUniform3fv(gl_IdVect[i].Id,1,lights.at(i)->getId());
          glUniform3fv(gl_IdVect[i].Is,1,lights.at(i)->getIs());
          glUniform3fv(gl_IdVect[i].coeficients,1,lights.at(i)->getCoeficients());
          glUniform3fv(gl_IdVect[i].position,1,lights.at(i)->getLightPosition());
          glUniform3fv(gl_IdVect[i].direction,1,direction);
          glUniform1f(gl_IdVect[i].angle,angle);

          cout << lights.at(i)->getIa() << endl;
          cout << lights.at(i)->getId() << endl;
          cout << lights.at(i)->getIs() << endl;
          cout << lights.at(i)->getLightPosition() << endl;
      }
}

void Scene::addLight(shared_ptr<Light> l) {
    lights.push_back(l);
}

/**
 * @brief Scene::setAmbientToGPU
 * @param program
 */
void Scene::setAmbientGlobalToGPU(shared_ptr<QGLShaderProgram> program){
    // TO DO: A implementar a la fase 1 de la practica 2
    GLuint globalLight = program->uniformLocation("globalAmbientLight");
    glUniform3fv(globalLight, 1, lightAmbientGlobal);

}

/**
 * @brief Scene::setCamera
 * @param Camera *
 */
void Scene::setCamera(shared_ptr<Camera> c) {
    camera = c;
}
/**
 * @brief Scene::calculCapsaMinCont3DEscena
 */

void Scene::calculCapsaMinCont3DEscena()
{
    Capsa3D c;
    vec3 pmax;

    if (objects.size()==1) {
        capsaMinima = objects[0]->calculCapsa3D();
        pmax[0] = capsaMinima.pmin[0]+capsaMinima.a;
        pmax[1] = capsaMinima.pmin[1]+capsaMinima.h;
        pmax[2] = capsaMinima.pmin[2]+capsaMinima.p;
    } else {
        capsaMinima.pmin[0]=200;
        capsaMinima.pmin[1]=200;
        capsaMinima.pmin[2]=200;
        pmax[0] = -200;
        pmax[1] = -200;
        pmax[2] = -200;
    }

    for (unsigned int i=0; i<objects.size(); i++) {
       c = objects[i]->calculCapsa3D();

       if (capsaMinima.pmin[0]>c.pmin[0]) capsaMinima.pmin[0] = c.pmin[0];
       if (capsaMinima.pmin[1]>c.pmin[1]) capsaMinima.pmin[1] = c.pmin[1];
       if (capsaMinima.pmin[2]>c.pmin[2]) capsaMinima.pmin[2] = c.pmin[2];
       if (pmax[0]<c.pmin[0]+c.a) pmax[0] = c.pmin[0]+c.a;
       if (pmax[1]<c.pmin[1]+c.h) pmax[1] = c.pmin[1]+c.h;
       if (pmax[2]<c.pmin[2]+c.p) pmax[2] = c.pmin[2]+c.p;
    }
    capsaMinima.a = pmax[0]-capsaMinima.pmin[0];
    capsaMinima.h = pmax[1]-capsaMinima.pmin[1];
    capsaMinima.p = pmax[2]-capsaMinima.pmin[2];
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        if (dynamic_pointer_cast<Animable>(objects[i]) ) objects[i]->update(nframe);
    }
}
