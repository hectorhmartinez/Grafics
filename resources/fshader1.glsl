#version 330

in vec4 color;
out vec4 colorOut;

void main()
{
    colorOut = vec4(color.x,color.y,color.z,0.5f);
}

