#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include <library/vec.h>
#include "Light.h"
using namespace Common;
class PointLight : public Light{
public:
    PointLight(vec3 Ia, vec3 Id, vec3 Is, vec4 position, vec3 coeficients);

};


#endif // POINTLIGHT_H
