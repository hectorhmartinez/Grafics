#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

uniform mat4 model_view;
uniform mat4 projection;
uniform vec4 lightDir;
out float intensity;
out vec4 Normal;
out vec4 Position;

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;
    intensity = dot(lightDir, vNormal);
    Normal = vNormal;
    Position = vPosition;
}
