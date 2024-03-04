#include "ScaleTG.h"

ScaleTG::ScaleTG(vec3 trasl, float scaleFactor): scalation(trasl)
{
    //matTG = scale(mat4(0), scalation);
    this->scaleFactor = scaleFactor;
}
ScaleTG::~ScaleTG()
{

}

