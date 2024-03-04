#version 330

in vec4 color;
out vec4 colorOut;

void main()
{
    colorOut =vec4((1.0-(15*gl_FragCoord.z)),(1.0-(15*gl_FragCoord.z)),(1.0-(15*gl_FragCoord.z)),color.w);

}

