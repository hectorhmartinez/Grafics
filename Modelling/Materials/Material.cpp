#include "Modelling/Materials/Material.h"


Material::Material() {
    this->Ka = vec3(0.2, 0.2, 0.2);
    this->Kd = vec3(0.8, 0.5, 0.5);
    this->Ks = vec3(1.0,1.0,1.0);
    this->Kd = vec3(0.5, 0.5, 0.5);
    this->shininess = 20.0;
}

Material::Material(vec3 a, vec3 d, vec3 s,vec3 t, float shin) {
    this->Ka = a;
    this->Kd = d;
    this->Ks = s;
    this->Kt = t;
    this->shininess = shin;
}

/**
 * Passa el material de CPU a GPU
 * @brief Material::toGPU
 * @param program
 */
void Material::toGPU(shared_ptr<QGLShaderProgram> program){
    // 1. En el codi de C++, per a passar els diferents atributs del shader declarem una estructura amb els
    // identificadors de les adreces de memòria corresponents a les variables definides a la GPU
    struct {
        GLuint Ka;
        GLuint Kd;
        GLuint Ks;
        GLuint Kt;
        GLuint shininess;
    } gl_IdMaterial;

    // 2. Otenció dels identificadors de la GPU
    gl_IdMaterial.Ka = program->uniformLocation("material.Ka");
    gl_IdMaterial.Kd = program->uniformLocation("material.Kd");
    gl_IdMaterial.Ks = program->uniformLocation("material.Ks");
    gl_IdMaterial.Kt = program->uniformLocation("material.Kt");
    gl_IdMaterial.shininess = program->uniformLocation("material.shininess");

    // 3. En el codi de C++, bind de les zones de memòria que corresponen a la GPU a valors de les variables de la CPU
    glUniform3fv(gl_IdMaterial.Ka, 1, this->Ka);
    glUniform3fv(gl_IdMaterial.Kd, 1, this->Kd);
    glUniform3fv(gl_IdMaterial.Ks, 1, this->Ks);
    glUniform3fv(gl_IdMaterial.Kt, 1, this->Kt);
    glUniform1f(gl_IdMaterial.shininess, this->shininess);

    qDebug() << "Material Sent to GPU" ;

}

