#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
#include <library/vec.h>
#include "Light.h"
using namespace Common;
class SpotLight : public Light{
public:
    SpotLight(vec3 Ia, vec3 Id, vec3 Is,vec4 position, vec3 coeficients, vec3 direction,float angle);
    vec3 getLightDirection();
    void setLightDirection(vec3 &dir);
    float getAngle();
    void setAngle(float &ang);
private:
    vec3 direction;
    float angle;
};

#endif // SPOTLIGHT_H
