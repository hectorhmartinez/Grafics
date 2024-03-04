#include "Modelling/Lights/Light.h"

/**
 * @brief Light::Light
 * @param t
 */
Light::Light(LightType t) {
    this->type = t;
}

Light::Light(LightType t, vec3 Ia, vec3 Id, vec3 Is,vec4 position,vec3 coeficients) {
    this->type = t;
    this->Ia = Ia;
    this->Id = Id;
    this->Is = Is;
    this->coeficients = coeficients;
    this->position = position;
}


vec3 Light::getId() {
    // TO DO: A canviar a la fase 1 de la practica 2
   return this->Id;
}


void Light::setId(vec3 i) {
    // TO DO: A canviar a la fase 1 de la practica 2
    this->Id = i;
}


vec4 Light::getLightPosition() {
    // TO DO: A canviar a la fase 1 de la practica 2
    return this->position;
}

void Light::setLightPosition(vec4 v) {
    // TO DO: A canviar a la fase 1 de la practica 2
    this->position = v;
}


vec3 Light::getIa() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       return this->Ia;
}


void Light::setIa(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    this->Ia = value;

}


vec3 Light::getIs() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       return this->Is;
}

void Light::setIs(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    this->Is = value;
}


vec3 Light::getCoeficients() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       return coeficients;
}

void Light::setCoeficients(const vec3 &value)
{
    this->coeficients = value;
}



LightType Light::getTipusLight() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
    return this->type;
}


void Light::setTipusLight(const LightType &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    this->type = value;
}
