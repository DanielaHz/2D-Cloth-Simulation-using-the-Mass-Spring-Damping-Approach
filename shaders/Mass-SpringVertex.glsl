#version 410 core
// this is the unique place where attribute data can place it
uniform mat4 MVP;
layout(location =0) in vec3 inPos;
layout(location =1) in vec3 inColour;
out vec3 colour;

void main()
{
    colour=inColour;
    gl_Position = MVP*vec4(inPos, 1.0);
}