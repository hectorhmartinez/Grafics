#version 330

uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;
in vec4 Normal;
in vec4 Position;
uniform vec3 AG;
// Struct que representa un material amb tots els seus parametres
struct MaterialStruct {
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    vec3 Kt;
    float shininess;
};

uniform MaterialStruct material;

struct LightComponents{
    int type;
    vec3 Ia;
    vec3 Id;
    vec3 Is;
    vec3 coeficients;
    vec4 position;
    vec3 direction;
    float angle;

};

uniform LightComponents lights[5];
in float intensity;
void main(void)
{
    vec4 color;
    if (intensity>0.95){
        color = vec4(1.0,0.5,0.5,1.0);
    }else if (intensity>0.5){
        color = vec4(0.6,0.3,0.3,1.0);
    }else if (intensity>0.25){
        color = vec4(0.4,0.2,0.2,1.0);
    }else {
        color = vec4(0.2,0.1,0.1,1.0);
    }
    gl_FragColor = color;

}
