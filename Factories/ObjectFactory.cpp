#include "ObjectFactory.h"

shared_ptr<Mesh> ObjectFactory::createObject(QString s)
{
    shared_ptr<Mesh> o;
    o = make_shared<Mesh>(100000,s);
    return o;
}

shared_ptr<Mesh> ObjectFactory::createObject( vector<vec3>points,QString s, float data) {
    shared_ptr<Mesh> o;
    o = make_shared<Mesh>(100000,s);
    return o;
}

shared_ptr<Mesh> ObjectFactory::createPlane( vector<vec3>points) {
    shared_ptr<Mesh> o;
    //o = make_shared<Plane>(points);
    return o;
}


