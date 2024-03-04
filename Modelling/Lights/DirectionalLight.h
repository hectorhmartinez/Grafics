#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include <library/vec.h>
#include "Light.h"
using namespace Common;
class DirectionalLight : public Light{
public:
    DirectionalLight(vec3 Ia, vec3 Id, vec3 Is,vec4 position, vec3 coeficients, vec3 direction);
    vec3 getLightDirection();
    void setLightDirection(vec3 &dir);
private:
    vec3 direction;
};



#endif // DIRECTIONALLIGHT_H
