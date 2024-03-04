#version 330

in vec4 Position;
in vec4 Normal;


uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;

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
uniform vec3 ambient;
uniform vec4 obs;
void main()
{
    // no la llegeix be per tant la inicialitzem aqui per fer proves
    vec4 position = vec4(10,10,20,0.0f);

    vec3 kd = material.Kd;
    vec3 ka = material.Ka;
    vec3 ks = material.Ks;
    float shininess = material.shininess;
    vec3 ambient = ambient;

    //color = vec4(ambient,1.0f);

    //color = vec4(1.0,0.0,0.0,0.0);
    vec3 ca = vec3(0.0,0.0,0.0);
    vec3 cd = vec3(0.0,0.0,0.0);
    vec3 cs = vec3(0.0,0.0,0.0);

    color = vec4(ambient*ka,0.0f);
    // i < nombre de llums
    for (int i = 0; i < 5; i++) {
       vec4 N = Normal;
       vec4 L = normalize(position - Position);
       cd = lights[i].Id*kd * max(dot(L, N),0.0f);
       vec4 V = normalize(obs - Position);

       vec4 H = normalize(L + V);
       cs = ks * lights[i].Is*pow(max(dot(N,H),0.0f),shininess);

       ca = ka *lights[i].Ia;
       color += vec4(ca+ cd + cs,1.0f);
    }
}
