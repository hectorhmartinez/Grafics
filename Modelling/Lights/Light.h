#pragma once

#include <library/vec.h>
using namespace Common;

// Tipus de Lights
enum LightType {Puntual, Direccional, Spot};

// Classe que representa els atributs d'una Light
// TO DO: A la fase 1 has d'incloure els atributs necessaris per codificar una llum

class Light {
    public:
        Light(LightType l);

        Light(LightType l, vec3 Ia, vec3 Id, vec3 Is, vec4 position, vec3 coeficients);

        virtual ~Light() = default;
        vec3 getIa() const;
        vec3 getId();
        vec3 getIs() const;
        vec3 getCoeficients() const;
        vec4 getLightPosition();
        LightType getTipusLight() const;

        void setLightPosition(vec4 v);
        void setIa(const vec3 &value);
        void setId(vec3 i);
        void setIs(const vec3 &value);
        void setCoeficients(const vec3 &value);
        void setTipusLight(const LightType &value);

    protected:
        vec3 Ia, Id, Is, coeficients;
        vec4 position;
        LightType type;
};

