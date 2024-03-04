#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec2 vCoordTexture;


uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;
out vec4 position;
out vec2 coordTexture;


void main(void)
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;
    position = vPosition;
    coordTexture = vCoordTexture;
    color = vColor;
}

