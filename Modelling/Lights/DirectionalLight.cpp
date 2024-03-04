#include "DirectionalLight.h"

DirectionalLight::DirectionalLight( vec3 Ia, vec3 Id, vec3 Is,vec4 position, vec3 coeficients, vec3 direction):Light(LightType::Direccional,Ia,Id,Is,position,coeficients){
    this->direction = direction;
}
vec3 DirectionalLight::getLightDirection(){
    return this->direction;
}
void DirectionalLight::setLightDirection(vec3 &dir){
    this->direction = dir;
}
