#ifndef SCALETG_H
#define SCALETG_H

#include "TG.h"

class ScaleTG : public TG
{
public:
    vec3 scalation;
    float scaleFactor;
    ScaleTG(vec3 trasl, float scaleFactor);
    virtual ~ScaleTG();
};

#endif // SCALETG_H
