#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;
struct LightComponents{
    vec3 Ia;
    vec3 Id;
    vec3 Is;
    vec3 coeficients;
    vec4 position;
    vec3 direction;
    float angle;
    int type;
};

uniform LightComponents lights[5];

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;
    color = vColor;
    //color = vec4(lights[0].Id[0],lights[0].Id[1],lights[0].Id[2],1.0f);
    //color = vec4(lights[1].Id[0],lights[1].Id[1],lights[1].Id[2],1.0f);
    //color = vec4(lights[2].Id[0],lights[2].Id[1],lights[2].Id[2],1.0f);
}
