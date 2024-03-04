#include "SpotLight.h"

SpotLight::SpotLight(vec3 Ia, vec3 Id, vec3 Is,vec4 position, vec3 coeficients, vec3 direction,float angle):Light(LightType::Spot,Ia,Id,Is,position,coeficients){
    this->direction = direction;
    this->angle = angle;
}
vec3 SpotLight::getLightDirection(){
    return this->direction;
}
void SpotLight::setLightDirection(vec3 &dir){
    this->direction = dir;
}
float SpotLight::getAngle(){
    return this->angle;
}
void SpotLight::setAngle(float &ang){
    this->angle = ang;
}

