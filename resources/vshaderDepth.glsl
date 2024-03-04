#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

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

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;
    color = vec4(material.Kt.x,material.Kt.y,material.Kt.z,1.0f);
}
