#version 330

in vec4 normal;
in vec4 position;
in vec2 coordTexture;
out vec4 color;

uniform sampler2D texMap;
uniform int hasTexture;

void main()
{
    // texture
    if(hasTexture==1){
        color = vec4((texture(texMap, coordTexture).rgb), 1.0f);
    }else{
        // transparent
        color = vec4(color.x,color.y,color.z,0.5f);
    }

}

