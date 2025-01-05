#version 410 core
layout(location =0) out vec4 fragColour;
in vec3 colour;
void main()
{
    fragColour = vec4(1.0, 0.0, 1.0, 1.0); // fucsia
    
}